#include "Parser.hpp"

#include <utility>
#include <algorithm>
#include "datastructure/Data.hpp"
#include "units/Unit.hpp"

RVector2       ParseMapData(const std::string& rawData) {
    auto pos = rawData.find('b') + 1;
    if (pos == std::string::npos)
        throw Parser::ParserException("bad Map format");
    return RVector2(std::stoi(rawData), std::stoi(&rawData.at(pos)));
}

std::shared_ptr<UnitData> ParseUnit(const std::string& rawData) {
    std::shared_ptr<UnitData> unitData = std::make_shared<UnitData>();
    auto pos = rawData.find("ID");
    if (pos == std::string::npos)
        throw Parser::ParserException("unit");
    pos += 2;
    auto sec_pos = rawData.find(',', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    unitData->SetPlayer(std::stoi(&rawData.at(pos), nullptr, 10));
    std::cout << "Player: " << unitData->GetPlayer() << std::endl;
    pos = ++sec_pos;
    sec_pos = rawData.find(':', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    unitData->SetId(std::stoi(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find('b', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    unitData->SetX(std::stol(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find(':', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    unitData->SetY(std::stol(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find(',', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    unitData->SetAtk(std::stof(&rawData.at(pos), nullptr));
    pos = ++sec_pos;
    unitData->SetMen(std::stoi(&rawData.at(pos), nullptr, 10));
    std::shared_ptr<Unit> mapUnit = std::make_shared<Unit>();
    unitData->SetMapUnit(mapUnit);
    return unitData;
}

void Parser::Map(const std::string& filename, Data& target) {
    std::ifstream file_map(filename);
    std::string line;
    std::string _mapSize;
    std::vector<std::string> rawUnits;
    if (!file_map.is_open())
        throw Parser::ParserException("bad file");
    std::getline(file_map, _mapSize);

    // init map
    RVector2 vec = ParseMapData(_mapSize);
    // load terrain etc...
    MapData newMap(vec);
    int mapIndex = Data::GetInstance().AddMapToCollection(newMap);

    // init units of that map
    while (std::getline(file_map, line))
        rawUnits.push_back(line);
    file_map.close();
    target.ClearUnits();
    for (auto &idx : rawUnits) {
        std::shared_ptr<UnitData> parsedUnit = ParseUnit(idx);
        parsedUnit->SetMapIdent(mapIndex);
        target.AddUnitToCollection(parsedUnit);
    }
}

bool DetectEmpty(const std::string& str) {
    if (std::all_of(str.begin(), str.end(), [] (std::string::value_type ch)
    { return isspace(ch) != 0; }))
        return true;
    return false;
}

void CleanLine(std::string& line) {
    size_t markBeginOfEnd = line.size();
    size_t markEndOfBegin = 0;
    for (auto i = 0; i < line.size() && std::isspace(line[i]); i++) {
        markEndOfBegin = i + 1;
    }
    for (auto i = line.size() - 1; std::isspace(line[i]); i--) {
        markBeginOfEnd = i;
        if (i <= 0)
            break;
    }
    line.erase(markBeginOfEnd, line.size() - markBeginOfEnd);
    line.erase(0, markEndOfBegin);
}

std::vector<std::string> StringSplit(const std::string& line) {
    std::vector<std::string> tokens;
    size_t  offset = 0;
    bool    jump = false;
    for (auto i = 0; i < line.size(); i++) {
        if (!jump && std::isspace(line[i])) {
            tokens.push_back(line.substr(offset, i - offset));
            offset = i + 1;
            jump = true;
        }
        else if (jump && std::isspace(line[i]))
            offset++;
        else
            jump = false;
    }
    if (offset != line.size() - 1)
        tokens.push_back(line.substr(offset));
    return tokens;
}

bool IsNumber(std::string& str) {
    for (auto &i: str) {
        if (!isdigit(i))
            return false;
    }
    return true;
}

void AssignTokens(std::vector<std::pair<token_t, std::string> >& stringTokenList, std::vector<std::string>& stringList) {
    std::string delimiterList = "=:;";
    std::pair<token_t, std::string> tokenPair;
    for (auto &i : stringList) {
        if (i == "begin")
            stringTokenList.emplace_back(token_t::BLOCK_BEGIN, i);
        else if (i == "end")
            stringTokenList.emplace_back(token_t::BLOCK_END, i);
        else if (i.length() == 1 && delimiterList.find(i[0]) != std::string::npos)
            stringTokenList.emplace_back(token_t::DELIMITER, i);
        else if (IsNumber(i))
            stringTokenList.emplace_back(token_t::NUMBER, i);
        else
            stringTokenList.emplace_back(token_t::STRING, i);
    }
}

void Tokenizer(std::vector<std::pair<token_t, std::string> >& stringTokenList, std::string& line) {
    if (DetectEmpty(line))
        return;
    CleanLine(line);
    std::vector<std::string> stringList = StringSplit(line);
    AssignTokens(stringTokenList, stringList);
}

Setting Parser::Settings(const std::string &filename) {
    Setting ret;
    std::ifstream file_setting(filename);
    std::string line;

    if (!file_setting.is_open())
        throw Parser::ParserException("bad file");
    std::vector<std::pair<token_t, std::string> > tokens;
    while (std::getline(file_setting, line)) {
        Tokenizer(tokens, line);
    }

    ret.TokenizedListToValues(tokens);

    return ret;
}

// const Data::MapData Parser::getMapData() const {
//     return _mData;
// }

// const std::vector<UnitData> Parser::getUnitData() const {
//     return _unitData;
// }

Parser::ParserException::ParserException(std::string cause) : _cause(std::move(cause)) { }

const char *Parser::ParserException::what() const noexcept {
    return _cause.c_str();
}
