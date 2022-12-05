#ifndef BANNERSCHLACHT_WRITE_HPP
#define BANNERSCHLACHT_WRITE_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "datastructure/Data.hpp"

/**
 * purpose: used to write data to files. Shall be used for custom formats etc.
 * */
class Writer {
private:
public:
    Writer() = default;
    ~Writer() {}
    //write mapsaves
    bool    MapSaves(std::string& absolutePath, Data/*::sub_class*/& mapToSave);
    //write unitdata
    class WriterException : public std::exception {
    private:
        std::string _cause;
    public:
        WriterException(constexpr std::string cause);
        ~WriterException() noexcept;
        [[nodiscard]] const char * what() noexcept const;
    }
};
#endif