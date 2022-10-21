#include "Writer.hpp"
#include <filesystem>

bool    Writer::MapSaves(std::string& absolutePath, Data/*::sub_class*/& mapToSave) {
    std::filesystem::path filePath(absolutePath);
    if (std::filesystem::exists(filePath)) {
        ;//TODO prompt ui popup
        return false;
    }
    std::ofstream file(absolutePath, ios_base::trunc);
    if (!file.isopen())
        return false;
        // throw Writer::WriterException("invalid path");
    /* structure:
        call subfunction for every class-datatype to write
    
    */

}

Writer::WriterException::WriterException(std::string cause) : _cause(cause) {}

const char* Writer::WriterException::what() const noexcept {
    return _cause.c_str();
}