#include "Lexicography.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (isspace(c)) { continue; }// skip whitespace
        if (isdigit(c) || c == '.'){ // parse number, including . 
            string num;
            while (isdigit(c) || c == '.') {
                num += c;
                c = input[++i];
            }
            i--;
            tokens.emplace_back(TokenType::NUMBER, num);
        }

        else if (isalpha(c)){ //parse variable or function
            string word;
            while (isalpha(c) || isdigit(c) || c == '_') {
                word += c;
                c = input[++i];
            }
            i--;

            if (word == "sin" ||
                word == "cos" ||
                word == "tan" ||
                word == "asin" ||
                word == "acos" ||
                word == "atan" ||
                word == "exp" ||
                word == "log" ||
                word == "sqrt" ||
                word == "logten" ||
                word == "ln" ||
                word == "abs" ||
                word == "pow"
            ){
                tokens.emplace_back(TokenType::FUNCTION, word);
            }
            else if (word == "preserve") { tokens.emplace_back(TokenType::PRESERVE, word); }
            else if (word == "remove") { tokens.emplace_back(TokenType::REMOVE, word); }
            else { tokens.emplace_back(TokenType::VARIABLE, word); }
        }
        else { // parse operators and punctuation, and throw runtime error when not recognized
            switch (c) {
                case '+': tokens.emplace_back(TokenType::PLUS, "+"); break;
                case '-': tokens.emplace_back(TokenType::MINUS, "-"); break;
                case '*': tokens.emplace_back(TokenType::MULTIPLY, "*"); break;
                case '/': tokens.emplace_back(TokenType::DIVIDE, "/"); break;
                case '^': tokens.emplace_back(TokenType::POWER, "^"); break;
                case '(': tokens.emplace_back(TokenType::LEFTPAREN, "("); break;
                case ')': tokens.emplace_back(TokenType::RIGHTPAREN, ")"); break;
                case '=': tokens.emplace_back(TokenType::ASSIGN, "="); break;
                case ',': tokens.emplace_back(TokenType::COMMA, ","); break;
                case '|': tokens.emplace_back(TokenType::ABS, "|"); break;
                default: throw runtime_error(string(1, c) + " is not recognized as a variable, function, or operation");
            }
        }
    }
    tokens.emplace_back(TokenType::END, " "); // end token
    return tokens;
}

