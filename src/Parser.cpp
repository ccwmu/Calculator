/**
 * @file Parser.cpp
 * @brief Implementation of parser class
 * @author Ethan Ye
 * @date 2025-8-19
*/

/*
This file uses recursive descent parsing to implement a heirarchical parsing structure. 
It uses a top-down approach to parse dynamic arrays of tokens into an AST that will return the 
final result of the expression. 
*/
#include "Parser.h"
#include "NumberNode.h"
#include "BinaryOpNode.h"
#include "FuncNode.h"
#include "UnaryOpNode.h"
#include "VariableNode.h"
#include "Lexicography.h"

#include <stdexcept>
#include <memory>
#include <cmath>
#include <iostream>

using namespace std;

// Constructur, initializes tokens and current index to 0
Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), currIndex(0) {}

// Helper functions to navigate tokens

// Increments to previous token if possible and return it, otherwise return current token
Token& Parser::prev() {
    if (currIndex > 0) { return tokens[--currIndex]; }
    else { return tokens[currIndex]; }
}

// Returns current token
Token& Parser::curr() {
    return tokens[currIndex];
}

// Increments to next token if possible and return it, otherwise return current token
Token& Parser::next() {
    if (currIndex < tokens.size()-1) { return tokens[++currIndex]; }
    else { return tokens[currIndex]; }
}

// Checks if current token matches given type
bool Parser::checkType(TokenType type) {
    return curr().type == type;
}

// Checks if next token matches given type
bool Parser::checkNext(TokenType type){
    return next().type == type;
}

// Public parse function, serves as entry point for main
unique_ptr<Node> Parser::parse(){
    return parseExpression();
}

// Begin private parsing functions

// Entry point for parsing expressions
unique_ptr<Node> Parser::parseExpression(){
    return parseAssignment();
}

// Parses assignment expressions of the form variable = expression
unique_ptr<Node> Parser::parseAssignment() {
    if (Parser::isAssignment()) { 
        if (currIndex + 1 < tokens.size() &&                   // Ensure that input follows correct assignment syntax
            tokens[currIndex].type == TokenType::VARIABLE &&
            tokens[currIndex + 1].type == TokenType::ASSIGN) { 
            assignmentVar = tokens[currIndex].value;
            currIndex += 2;
            return parseAddition(); // Parse the expression on the right side of the assignment, which can include all other types of expressions
        }
        else { throw runtime_error("use [variable] = [expression] for assignment"); } // invalid assignment syntax
    }
    return parseAddition(); // if there is no assignment, then continue parsing.
}

unique_ptr<Node> Parser::parseAddition() { 
    unique_ptr<Node> left = parseMultiplication(); // continue parsing left side
    while (checkType(TokenType::PLUS) || checkType(TokenType::MINUS)) { // if there is a minus or a plus
		TokenType op = curr().type; // plus/minus operator
        next(); // move to next token
        unique_ptr<Node> right = parseMultiplication(); // parse right side

        // left = (op == TokenType::PLUS) ? 
        //     make_unique<AddNode>(move(left), move(right)) : 
        //     make_unique<SubtractNode>(move(left), move(right));
        if (op == TokenType::PLUS) { left = make_unique<AddNode>(move(left), move(right)); } // make addition node from the left and right sides of the operator
		else { left = make_unique<SubtractNode>(move(left), move(right)); } // make subtraction node from the left and right sides of the operator

    }
    return left; // return the left side which now contains the rest of the expression tree
}

unique_ptr<Node> Parser::parseMultiplication() {
    unique_ptr<Node> left = parsePower(); // continue parsing left side
	while (checkType(TokenType::MULTIPLY) || checkType(TokenType::DIVIDE)) { // if there is a multiply or divide
		TokenType op = curr().type; // multiply/divide operator
		next(); // move to next token
        unique_ptr<Node> right = parsePower(); // continue parse right side

        // left = (op == TokenType::MULTIPLY) ? 
        //     make_unique<MultiplyNode>(move(left), move(right)) : 
        //     make_unique<DivideNode>(move(left), move(right));

		if (op == TokenType::MULTIPLY) { left = make_unique<MultiplyNode>(move(left), move(right)); } // make multiplication node from the left and right sides of the operator
		else { left = make_unique<DivideNode>(move(left), move(right)); } // make division node from the left and right sides of the operator

    }
    return left;
}

unique_ptr<Node> Parser::parsePower() { // right associative
	unique_ptr<Node> left = parseUnary(); // continue parsing left side 
    if (checkType(TokenType::POWER)) { 
        next();
        unique_ptr<Node> right = parsePower(); // parse right side (right-associative)

        return make_unique<PowerNode>(move(left), move(right)); // make power node from left and right sides
    }
    return left;
}

unique_ptr<Node> Parser::parseUnary() {
    if (checkType(TokenType::MINUS)) {
        next();
        return make_unique<NegateNode>(parseUnary());
    }
    return parsePrimary();
}

unique_ptr<Node> Parser::parsePrimary() {
    // Numbers
    if (checkType(TokenType::NUMBER)) {
        long double value = stod(curr().value);
        next();
        return make_unique<NumberNode>(value);
    }

    // Vars

    if (checkType(TokenType::VARIABLE)) {
        string name = curr().value;
        next();
        return make_unique<VariableNode>(name);
    }

    // Absolute value

    if (checkType(TokenType::ABS)) {
        next();
        unique_ptr<Node> expr = parseExpression();
        if (!checkType(TokenType::ABS)) {
            throw runtime_error("expected closing | for absolute value expression");
        }
        next();
        return make_unique<AbsNode>(move(expr));
    }

    // Functions 

    if (checkType(TokenType::FUNCTION)) {
        string funcName = curr().value;
        next();

        if (!checkType(TokenType::LEFTPAREN)) {
                throw runtime_error("expected '(' after function name");
            }
        next();
        if (funcName == "log") {
            unique_ptr<Node> arg1 = parseExpression();
            if (!checkType(TokenType::COMMA)) {
                throw runtime_error("expected ',' between log arguments");
            }
            next();
            unique_ptr<Node> arg2 = parseExpression();

            if (!checkType(TokenType::RIGHTPAREN)) {
                throw runtime_error("expected ')' after function arguments");
            }
            next();
            return make_unique<LogNode>(move(arg1), move(arg2));
        }

        unique_ptr<Node> argument = parseExpression();

        if (!checkType(TokenType::RIGHTPAREN)) {
            throw runtime_error("expected ')' after function argument");
        }
        next();

        if (funcName == "sin") { return make_unique<SinNode>(move(argument)); }
        if (funcName == "cos") { return make_unique<CosNode>(move(argument)); }
        if (funcName == "tan") { return make_unique<TanNode>(move(argument)); }
        if (funcName == "asin") { return make_unique<ArcSinNode>(move(argument)); }
        if (funcName == "acos") { return make_unique<ArcCosNode>(move(argument)); }
        if (funcName == "atan") { return make_unique<ArcTanNode>(move(argument)); }
        if (funcName == "exp") { return make_unique<ExpNode>(move(argument)); }
        if (funcName == "ln") { return make_unique<LnNode>(move(argument)); }
        if (funcName == "log10") { return make_unique<LogTenNode>(move(argument)); }
        if (funcName == "sqrt") { return make_unique<SqrtNode>(move(argument)); }
        if (funcName == "abs") { return make_unique<AbsNode>(move(argument)); }

        throw runtime_error(funcName + " is not recognized as a variable, function, or operation");

    }

    if (checkType(TokenType::LEFTPAREN)) {
        next();
        unique_ptr<Node> expr = parseExpression();
        if (!checkType(TokenType::RIGHTPAREN)) {
            throw runtime_error("expected ')' after expression");
        }
        next();
        return expr;
    }

    throw runtime_error("unexpected element in expression");

}

bool Parser::parsePreserve() {
    if (tokens.size() == 3 && tokens[0].type == TokenType::PRESERVE && tokens[1].type == TokenType::VARIABLE) {
		assignmentVar = tokens[1].value;
        return true;
    }
    else if (any_of(tokens.begin(), tokens.end(), [](const Token& t) { return t.type == TokenType::PRESERVE; })) {
        throw runtime_error("invalid preserve variable syntax! Use remove [variable] to remove a variable from preserved variables");
    }
    return false;
}

bool Parser::parseRemove() {
    if (tokens.size() == 3 && tokens[0].type == TokenType::REMOVE && tokens[1].type == TokenType::VARIABLE) {
		assignmentVar = tokens[1].value;
        return true;
    }
    else if (any_of(tokens.begin(), tokens.end(), [](const Token& t) { return t.type == TokenType::REMOVE; })) {
        throw runtime_error("invalid remove variable syntax! Use remove [variable] to remove a variable from preserved variables");
    }
    return false;
}
