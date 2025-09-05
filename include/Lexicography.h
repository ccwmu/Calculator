#ifndef LEXICOGRAPHY_H
#define LEXICOGRAPHY_H

#include <string>
#include <vector>

enum class TokenType {
    NUMBER, 
    VARIABLE, 
    FUNCTION, 
    PLUS, 
    MINUS, 
    MULTIPLY, 
    DIVIDE, 
    POWER, 
    LEFTPAREN, 
    RIGHTPAREN, 
    ASSIGN, 
    COMMA, 
    ABS,
    END, 
    PRESERVE, 
    REMOVE
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& value) : type(type), value(value) {}
};

std::vector<Token> tokenize(const std::string& input);

#endif //LEXICOGRAPHY_H