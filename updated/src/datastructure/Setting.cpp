//
// Created by Jascha Kasper on 1/7/23.
//

#include "Setting.hpp"

std::string GetTokenName(enum e_tokens token) {
    switch (token) {
        case STRING:
            return "STRING";
        case NUMBER:
            return "NUMBER";
        case DELIMITER:
            return "DELIMITER";
        case BLOCK_BEGIN:
            return "BLOCK_BEGIN";
        case BLOCK_END:
            return "BLOCK_END";
        case NONE:
            return "NONE";
    }
    return "NONE";
}

bool Setting::TokenizedListToValues(std::vector<std::pair<token_t, std::string> >& tokenizedList) {
    token_t expectedToken = NONE;
    token_t lastToken = NONE;
    std::string markedToken;
    std::stack<std::string> activeBlocks;

    for (auto& i : tokenizedList) {
        std::cout << i.second << std::endl;
    }

    for (auto &i : tokenizedList) {
        std::cout << "marked Token:    " << markedToken << std::endl;
        std::cout << "last Token:      " << GetTokenName(lastToken) << std::endl;
        std::cout << "expected Token:  " << GetTokenName(expectedToken) << std::endl;
        std::cout << GetTokenName(i.first) << "\t" << i.second << std::endl << std::endl;
        if ((expectedToken == NONE &&
                ( i.first == DELIMITER)) ||
            (expectedToken != NONE && i.first != expectedToken)
                ) {
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
                markedToken = "";
                expectedToken = NONE;
            }
            else if (lastToken == DELIMITER && i.first == NUMBER) {
                Setting::AddKeyValue(activeBlocks, markedToken, i.second);
                markedToken = "";
                expectedToken = NONE;
            }
            else if (lastToken == BLOCK_BEGIN && i.first == STRING) {
                Setting::CheckValue(i.second, BLOCK_BEGIN);
                activeBlocks.push(i.second);
                expectedToken = NONE;
            }
            else if (i.first == BLOCK_END) {
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
    return true;
}

bool WordCombination(std::string& target, std::string first, std::string second) {
    if (target == first + second)
        return true;
    if (target == first + "_" + second)
        return true;
    first[0] = toupper(first[0]);
    second[0] = toupper(second[0]);
    if (target == first + second)
        return true;
    if (target == first + "_" + second)
        return true;
    return false;
}
///enable if needed
//bool WordCombination(std::string& target, std::string first, std::string second, std::string third) {
//    if (target == first + second + third)
//        return true;
//    if (target == first + "_" + second + "_" + third)
//        return true;
//    first[0] = toupper(first[0]);
//    second[0] = toupper(second[0]);
//    third[0] = toupper(third[0]);
//    if (target == first + second + third)
//        return true;
//    if (target == first + "_" + second+ "_" + third)
//        return true;
//    return false;
//}

token_t Setting::CheckValue(std::string &markedToken, token_t tokenType) {
    if (tokenType == BLOCK_BEGIN && (
            markedToken == "Textures" || markedToken == "textures" || markedToken == "Maps" || markedToken == "maps"))
        return BLOCK_BEGIN;
    else if (tokenType == DELIMITER && (WordCombination(markedToken, "window", "height") || WordCombination(markedToken, "window", "width")))
        return NUMBER;
    return STRING;
}

void Setting::AddKeyValue(std::stack<std::string> &blocks, std::string &markedToken, std::string &currentToken) {
    char *controlPointer;
    if (blocks.empty()) {
        if (WordCombination(markedToken, "window", "height")) {
            windowHeight = strtol(currentToken.c_str(), &controlPointer, 10);
            if (*controlPointer != '\0')
                throw Setting::ValueException("invalid value: must be a integer type value");
        }
        if (WordCombination(markedToken, "window", "width")){
            windowWidth = strtol(currentToken.c_str(), &controlPointer, 10);
            if (*controlPointer != '\0')
                throw Setting::ValueException("invalid value: must be a integer type value");
        }
    }
    else if (blocks.top() == "Textures" || blocks.top() == "textures") {
        textureList.insert(std::pair<std::string, std::string>(markedToken, currentToken));
    } else if (blocks.top() == "Maps" || blocks.top() == "maps") {
        mapFolderPaths.push_back(currentToken);
    }
}

Setting::ValueException::ValueException(std::string cause) : _cause(std::move(cause)) { }

const char *Setting::ValueException::what() const noexcept {
    return _cause.c_str();
}
