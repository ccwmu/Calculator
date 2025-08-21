#ifndef LEXICOGRAPHY_H
#define LEXICOGRAPHY_H

#include "Node.h"
#include <vector>
using namespace std;

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
    END
};

struct Token {
    TokenType type;
    string value;

    Token(TokenType type, const string& value) : type(type), value(value) {}
};

vector<Token> tokenize(const string& input);

#endif //LEXICOGRAPHY_H