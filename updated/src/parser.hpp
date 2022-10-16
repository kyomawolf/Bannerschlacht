#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "data.hpp"

class parser {
private:
    std::map<std::string, std::string> fileList;
    std::string                        map_size;
    std::vector<data::UnitData>        unitData;
    data::MapData                      mData;
public:
    parser() = default;
    void    Map(const std::string& filename);

    [[nodiscard]] const data::MapData getMapData() const;
    [[nodiscard]] const std::vector<data::UnitData> getUnitData() const;
    /* exceptions */
    class parserException : public std::exception {
    private:
        const std::string _cause;
    public:
        parserException(std::string  cause);
        [[nodiscard]] const char * what() const noexcept override;
    };
};

std::ostream& operator<<(std::ostream& o, const data::UnitData& data);

#endif /*PARSER_HPP*/