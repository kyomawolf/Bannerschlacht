#include "Parser.hpp"

#include <utility>
#include "Data.hpp"
#include "Unit.hpp"

std::ostream& operator<<(std::ostream& o, const Data::UnitData& data) {
    o << "attack: "     << data.atk << std::endl
      << "defense: "    << data.def << std::endl
      << "men: "        << data.men << std::endl
      << "movement: "   << data.mov << std::endl
      << "morale: "     << data.mor << std::endl
      << "id: "         << data.id << std::endl
      << "pos-x: "      << data.x << std::endl
      << "pos-y: "      << data.y << std::endl
      << "player-id: "  << data.player << std::endl;
    return o;
}

RVector2       ParseMapData(const std::string& rawData) {
    auto pos = rawData.find('b') + 1;
    if (pos == std::string::npos)
        throw Parser::ParserException("bad Map format");
    return RVector2(std::stoi(rawData), std::stoi(&rawData.at(pos)));
}

Data::UnitData ParseUnit(const std::string& rawData) {
    Data::UnitData new_data = {0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr}; //todo allocator
    auto pos = rawData.find("ID");
    if (pos == std::string::npos)
        throw Parser::ParserException("unit");
    pos += 2;
    auto sec_pos = rawData.find(',', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.player = std::stoi(&rawData.at(pos), nullptr, 10);
    pos = ++sec_pos;
    sec_pos = rawData.find(':', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.id = std::stoi(&rawData.at(pos), nullptr, 10);
    pos = ++sec_pos;
    sec_pos = rawData.find('b', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.x = std::stol(&rawData.at(pos), nullptr, 10);
    pos = ++sec_pos;
    sec_pos = rawData.find(':', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.y = std::stol(&rawData.at(pos), nullptr, 10);
    pos = ++sec_pos;
    sec_pos = rawData.find(',', pos);
    if (sec_pos == std::string::npos)
        throw Parser::ParserException("unit");
    new_data.atk = std::stof(&rawData.at(pos), nullptr);
    pos = ++sec_pos;
    new_data.men = std::stoi(&rawData.at(pos), nullptr, 10);
    std::cout << new_data << std::endl;
    new_data.class_d = new Unit(new_data);
    return new_data;
}

void Parser::Map(const std::string& filename) {///TODO refactor
    std::ifstream file_map(filename);
    std::string line;
    std::vector<std::string> rawUnits;
    if (!file_map.is_open())
        throw Parser::ParserException("bad file");
    _fileList.insert(std::pair<std::string, std::string>("GameMap", filename));
    std::getline(file_map, _mapSize);
    while (std::getline(file_map, line))
        rawUnits.push_back(line);
    file_map.close();
    for (auto i = rawUnits.begin(); i != rawUnits.end(); i++)
        _unitData.push_back(ParseUnit(*i));
    RVector2 vec = ParseMapData(_mapSize);
    _mData.width = vec.x;
    _mData.height = vec.y;
////    for (auto i = parsedUnits.begin(); i != parsedUnits.end(); i++)
////       std::cout << *i << std::endl;
}

const Data::MapData Parser::getMapData() const {
    return _mData;
}

const std::vector<Data::UnitData> Parser::getUnitData() const {
    return _unitData;
}

Parser::ParserException::ParserException(std::string cause) : _cause(std::move(cause)) { }

const char *Parser::ParserException::what() const noexcept {
    return _cause.c_str();
}
