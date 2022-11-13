#include "Parser.hpp"

#include <utility>
#include "datastructure/Data.hpp"
#include "units/Unit.hpp"

RVector2       ParseMapData(const std::string& rawData) {
    auto pos = rawData.find('b') + 1;
    if (pos == std::string::npos)
        throw Parser::ParserException("bad Map format");
    return RVector2(std::stoi(rawData), std::stoi(&rawData.at(pos)));
}

UnitData ParseUnit(const std::string& rawData) {
    UnitData new_data;
    auto pos = rawData.find("ID");
    if (pos == std::string::npos)
        throw Parser::ParserException("unit");
    pos += 2;
    auto sec_pos = rawData.find(',', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.SetPlayer(std::stoi(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find(':', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.SetId(std::stoi(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find('b', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.SetX(std::stol(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find(':', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.SetY(std::stol(&rawData.at(pos), nullptr, 10));
    pos = ++sec_pos;
    sec_pos = rawData.find(',', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.SetAtk(std::stof(&rawData.at(pos), nullptr));
    pos = ++sec_pos;
    new_data.SetMen(std::stoi(&rawData.at(pos), nullptr, 10));
    std::cout << new_data << std::endl;
    new_data.SetClass_d(new Unit(new_data));
    return new_data;
}

void Parser::Map(const std::string& filename, Data& target) {///TODO refactor
    std::ifstream file_map(filename);
    std::string line;
    std::vector<std::string> rawUnits;
    if (!file_map.is_open())
        throw Parser::ParserException("bad file");
    // _fileList.insert(std::pair<std::string, std::string>("GameMap", filename));
    std::getline(file_map, _mapSize);
    while (std::getline(file_map, line))
        rawUnits.push_back(line);
    file_map.close();
    for (auto i = rawUnits.begin(); i != rawUnits.end(); i++)
        target.vecUnits.push_back(new Unit(ParseUnit(*i)));
    RVector2 vec = ParseMapData(_mapSize);
    Data::DataLink  map_data = {Data::DIdent::MAP, new MapData(vec.x, vec.y)};
    target.vecLink.push_back(map_data   );
////    for (auto i = parsedUnits.begin(); i != parsedUnits.end(); i++)
////       std::cout << *i << std::endl;
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
