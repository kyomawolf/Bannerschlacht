//
// Created by Jascha Kasper on 1/7/23.
//

#ifndef BANNERSCHLACHT_SETTING_HPP
#define BANNERSCHLACHT_SETTING_HPP

#include "raylib-cpp.hpp"
#include <map>
#include <stack>
#include <vector>

typedef enum e_tokens{STRING = 0, NUMBER, DELIMITER, BLOCK_BEGIN, BLOCK_END, NONE } token_t;

struct Setting {
    long         windowHeight;
    long         windowWidth;
    std::string version = "0.0.2";
    std::string programName = "Bannerschlacht";
    std::string defaultMapFolderPath = {"maps/"};
    std::map<std::string, std::string> textureList;
    std::vector<std::string>           mapFolderPaths;
    bool TokenizedListToValues(std::vector<std::pair<token_t, std::string> >& tokenizedList);
    token_t CheckValue(std::string& markedToken, token_t tokenType);
    void    AddKeyValue(std::stack<std::string>& blocks, std::string& markedToken, std::string& currentToken);


    //exceptions
    class ValueException : public std::exception {
    private:
        const std::string _cause;
    public:
        explicit ValueException(std::string  cause);
        [[nodiscard]] const char * what() const noexcept override;
    };
};


#endif //BANNERSCHLACHT_SETTING_HPP
