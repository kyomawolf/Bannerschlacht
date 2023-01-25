//
// Created by Jascha Kasper on 1/7/23.
//

#include "Setting.hpp"

bool Setting::TokenizedListToValues(std::vector<std::pair<token_t, std::string> >& tokenizedList) {
    token_t expectedToken = NONE;
    token_t lastToken = NONE;
    std::string markedToken;
    std::stack<std::string> activeBlocks;

    for (auto &i : tokenizedList) {
        if ((expectedToken == NONE &&
             (i.first == BLOCK_END ||
              i.first == DELIMITER)) ||
            (expectedToken != NONE && i.first != expectedToken)
                ) {
            std::cout << i.second << std::endl;
            switch (expectedToken) {
                case STRING:
                    throw Setting::ValueException("unexpected token: string expected");
                case NUMBER:
                    throw Setting::ValueException("unexpected token: number expected");
                case DELIMITER:
                    throw Setting::ValueException("unexpected token: delimiter token expected");
                case BLOCK_BEGIN:
                    throw Setting::ValueException("unexpected token: begin-block expected");
                case BLOCK_END:
                    throw Setting::ValueException("unexpected token: end-block expected");
                default:
                    throw Setting::ValueException("unexpected token: not a default token");
            }
            /// if no token is expected and its not ending a scope
        } else if (expectedToken == NONE && i.first != BLOCK_END) {
            switch (i.first) {
                case STRING:
                    if (!activeBlocks.empty() && (activeBlocks.top() == "Maps" || activeBlocks.top() == "maps")) {
                        AddKeyValue(activeBlocks, markedToken, i.second);
                        expectedToken = NONE;
                    }
                    expectedToken = DELIMITER;
                    markedToken = i.second;
                    break;
                case BLOCK_BEGIN:
                    expectedToken = STRING;
                    break;
                default:
                    expectedToken = NONE;
            }
        } else {
            if (lastToken == DELIMITER && i.first == STRING) {
                Setting::AddKeyValue(activeBlocks, markedToken, i.second);
            }
            if (lastToken == BLOCK_BEGIN && i.first == STRING) {
                Setting::CheckValue(i.second, BLOCK_BEGIN);
                activeBlocks.push(i.second);
            }
            if (i.first == BLOCK_END) {
                if (activeBlocks.empty())
                    throw Setting::ValueException("No Block to end");
                else
                    activeBlocks.pop();
            }
        }
        if (i.first == DELIMITER) {
            expectedToken = Setting::CheckValue(markedToken, DELIMITER);
        }
        lastToken = i.first;
    }
//
//    char* controlPointer;
//    if (name == "window_width") {
//
//    } else if (name == "window_height") {
//        windowHeight = strtol(value.c_str(), &controlPointer, 10);
//        if (*controlPointer != '\0')
//            throw Setting::ValueException("invalid value: must be a integer type value");
//    } else if (name == "version") {
//        version = value.substr();
//        if (version.length() == 0)
//            throw Setting::ValueException("invalid value: cannot be empty");
//    } else if (name == "program_name") {
//        programName = value.substr();
//        if (version.length() == 0)
//            throw Setting::ValueException("invalid value: cannot be empty");
//    } else if (name == "relative_maps_folder_path") {
//        relativeMapFolderPath = value.substr();
//        if (version.length() == 0)
//            throw Setting::ValueException("invalid value: cannot be empty");
//    } else
//        return false;
//    return true;
}

token_t Setting::CheckValue(std::string &markedToken, token_t tokenType) {
    if (tokenType == BLOCK_BEGIN && (
            markedToken == "Textures" || markedToken == "textures" || markedToken == "Maps" || markedToken == "maps"))
        return BLOCK_BEGIN;
    else if (tokenType == DELIMITER && (
            markedToken == "WindowHeight" || markedToken == "windowheight" || markedToken == "Windowheight" ||
            markedToken == "WindowWidth" || markedToken == "windowwidth" || markedToken == "Windowwidth"))
        return NUMBER;
    return STRING;
}

void Setting::AddKeyValue(std::stack<std::string> &blocks, std::string &markedToken, std::string &currentToken) {
    char *controlPointer;
    if (blocks.empty()) {
        if (markedToken == "WindowHeight" || markedToken == "windowheight" || markedToken == "Windowheight") {
            windowHeight = strtol(currentToken.c_str(), &controlPointer, 10);
            if (*controlPointer != '\0')
                throw Setting::ValueException("invalid value: must be a integer type value");
        }
        if (markedToken == "WindowWidth" || markedToken == "windowwidth" || markedToken == "Windowwidth"){
            windowWidth = strtol(currentToken.c_str(), &controlPointer, 10);
            if (*controlPointer != '\0')
                throw Setting::ValueException("invalid value: must be a integer type value");
        }
    }
    if (blocks.top() == "Textures" || blocks.top() == "textures") {
        textureList.insert(std::pair<std::string, std::string>(markedToken, currentToken));
    } else if (blocks.top() == "Maps" || blocks.top() == "maps") {
        mapFolderPaths.push_back(currentToken);
    }
}

Setting::ValueException::ValueException(std::string cause) : _cause(std::move(cause)) { }

const char *Setting::ValueException::what() const noexcept {
    return _cause.c_str();
}
