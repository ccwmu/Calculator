#ifndef PARSER_H
#define PARSER_H
#include "Lexicography.h"
#include "Node.h"
#include <memory>
#include <vector>

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    size_t currIndex;
    bool containsNewVar = false;
    string assignmentVar;
    
    Token& prev();                   // Previous Token
    Token& curr();                   // Current Token
    Token& next();                   // Next Token

    bool checkType(TokenType type);  // Current Token Type
    bool checkNext(TokenType type);  // Next Token Type

    // Parsing functions
    unique_ptr<Node> parseExpression();     // Entry
    unique_ptr<Node> parseAssignment();     // Assignment (x = <expr>)
    unique_ptr<Node> parseAddition();       // + and -
    unique_ptr<Node> parseMultiplication(); // * and /
    unique_ptr<Node> parsePower();          // ^ (right associative)
    unique_ptr<Node> parseUnary();          // +x, -x
    unique_ptr<Node> parsePrimary();        // Numbers, variables, parentheses, functions

public: 
    Parser(vector<Token> tokens);
    unique_ptr<Node> parse();
    bool isAssignment() const {
        for (Token token : tokens) {
            if (token.type == TokenType::ASSIGN) { return true; }
		}
        return false;
    }
    string getAssignVar() const { return assignmentVar; }



};



#endif //PARSER_H