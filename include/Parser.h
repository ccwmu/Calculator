

#ifndef PARSER_H
#define PARSER_H
#include "Lexicography.h"
#include "Node.h"
#include <memory>
#include <vector>
#include <stdexcept>


class Parser {
private:

    std::vector<Token> tokens; ///<
    std::size_t currIndex;
    bool containsNewVar = false;
    std::string assignmentVar;
    
    Token& prev();                   // Previous Token
    Token& curr();                   // Current Token
    Token& next();                   // Next Token

    bool checkType(TokenType type);  // Current Token Type
    bool checkNext(TokenType type);  // Next Token Type

    // Parsing functions
    std::unique_ptr<Node> parseExpression();     // Entry
    std::unique_ptr<Node> parseAssignment();     // Assignment (x = <expr>)
    std::unique_ptr<Node> parseAddition();       // + and -
    std::unique_ptr<Node> parseMultiplication(); // * and /
    std::unique_ptr<Node> parsePower();          // ^ (right associative)
    std::unique_ptr<Node> parseUnary();          // +x, -x
    std::unique_ptr<Node> parsePrimary();        // Numbers, variables, parentheses, functions

public: 
    Parser(std::vector<Token> tokens);
    std::unique_ptr<Node> parse();
    bool isAssignment() const {
        for (const Token token : tokens) {
            if (token.type == TokenType::ASSIGN) { return true; }
		}
        return false;
    }
    std::string getAssignVar() const { return assignmentVar; }

    bool parsePreserve();
    bool parseRemove();

};



#endif //PARSER_H