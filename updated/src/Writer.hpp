#ifndef BANNERSCHLACHT_WRITE_HPP
#define BANNERSCHLACHT_WRITE_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "datastructure/Data.hpp"

//used to write data to file
class Writer {
private:
public:
    Write() = default;
    ~Writer() {}
    //write mapsaves
    bool    MapSaves(std::string& absolutePath, Data/*::sub_class*/& mapToSave);
    //write unitdata
    class WriterException : public std::exception {
    private:
        std::string _cause;
    public:
        WriterException(constexpr std::string cause);
        [[nodiscard]] const char * what() const noexcept override;
    }
};
#endif