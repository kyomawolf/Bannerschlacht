#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "datastructure/Data.hpp"

class Parser {
private:

    //TODO refactor (and throw out) variables
    // std::map<std::string, std::string> _fileList;
    std::string                        _mapSize;
    // std::vector<Data::UnitData>        _unitData;
    // Data::MapData                      _mData;
public:
    Parser() = default;
    void    Map(const std::string& filename, Data& target);

    // [[nodiscard]] const Data::MapData getMapData()                const;
    // [[nodiscard]] const std::vector<Data::UnitData> getUnitData() const;
    /* exceptions */
    class ParserException : public std::exception {
    private:
        const std::string _cause;
    public:
        ParserException(std::string  cause);
        [[nodiscard]] const char * what() const noexcept override;
    };
};

#endif /*PARSER_HPP*/