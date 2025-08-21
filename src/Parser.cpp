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




Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), currIndex(0), assignment(false) {}

Token& Parser::prev() {
    if (currIndex > 0) { return tokens[--currIndex]; }
    else { return tokens[currIndex]; }
}
Token& Parser::curr() {
    return tokens[currIndex];
}

Token& Parser::next() {
    if (currIndex < tokens.size()-1) { return tokens[++currIndex]; }
    else { return tokens[currIndex]; }
}

bool Parser::checkType(TokenType type) {
    return curr().type == type;
}

bool Parser::checkNext(TokenType type){
    return next().type == type;
}

unique_ptr<Node> Parser::parse(){
    return parseExpression();
}

unique_ptr<Node> Parser::parseExpression(){
    return parseAssignment();
}

unique_ptr<Node> Parser::parseAssignment() {
    if (currIndex + 1 < tokens.size() &&
        tokens[currIndex].type == TokenType::VARIABLE &&
        tokens[currIndex + 1].type == TokenType::ASSIGN) {
        assignment = true;
        assignmentVar = tokens[currIndex].value;
        currIndex += 2;
        return parseAddition();
    }
    return parseAddition();
}

unique_ptr<Node> Parser::parseAddition() {
    unique_ptr<Node> left = parseMultiplication();
    while (checkType(TokenType::PLUS) || checkType(TokenType::MINUS)) {
        TokenType op = curr().type;
        next();
        unique_ptr<Node> right = parseMultiplication();

        // left = (op == TokenType::PLUS) ? 
        //     make_unique<AddNode>(move(left), move(right)) : 
        //     make_unique<SubtractNode>(move(left), move(right));
        if (op == TokenType::PLUS) { left = make_unique<AddNode>(move(left), move(right)); }
        else { left = make_unique<SubtractNode>(move(left), move(right)); }

    }
    return left;
}

unique_ptr<Node> Parser::parseMultiplication() {
    unique_ptr<Node> left = parsePower();
    while (checkType(TokenType::MULTIPLY) || checkType(TokenType::DIVIDE)) {
        TokenType op = curr().type;
        next();
        unique_ptr<Node> right = parsePower();

        // left = (op == TokenType::MULTIPLY) ? 
        //     make_unique<MultiplyNode>(move(left), move(right)) : 
        //     make_unique<DivideNode>(move(left), move(right));

        if (op == TokenType::MULTIPLY) { left = make_unique<MultiplyNode>(move(left), move(right)); } 
        else { left = make_unique<DivideNode>(move(left), move(right)); }

    }
    return left;
}

unique_ptr<Node> Parser::parsePower() {
    unique_ptr<Node> left = parseUnary();
    if (checkType(TokenType::POWER)) {
        next();
        unique_ptr<Node> right = parsePower();

        return make_unique<PowerNode>(move(left), move(right));
    }
    return left;
}

unique_ptr<Node> Parser::parseUnary() {
    if (checkType(TokenType::PLUS)) {
        next();
        return parseUnary();
    } else if (checkType(TokenType::MINUS)) {
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
            throw runtime_error("Expected closing | for absolute value expression");
        }
        next();
        return make_unique<AbsNode>(move(expr));
    }

    // Functions 

    if (checkType(TokenType::FUNCTION)) {
        string funcName = curr().value;
        next();

        if (!checkType(TokenType::LEFTPAREN)) {
                throw runtime_error("Expected '(' after function name");
            }
        next();
        if (funcName == "log") {
            unique_ptr<Node> arg1 = parseExpression();
            if (!checkType(TokenType::COMMA)) {
                throw runtime_error("Expected ',' between log arguments");
            }
            next();
            unique_ptr<Node> arg2 = parseExpression();

            if (!checkType(TokenType::RIGHTPAREN)) {
                throw runtime_error("Expected ')' after function arguments");
            }
            next();
            return make_unique<LogNode>(move(arg1), move(arg2));
        }

        unique_ptr<Node> argument = parseExpression();

        if (!checkType(TokenType::RIGHTPAREN)) {
            throw runtime_error("Expected ')' after function argument");
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

        throw runtime_error("Unknown function: " + funcName);

    }

    if (checkType(TokenType::LEFTPAREN)) {
        next();
        unique_ptr<Node> expr = parseExpression();
        if (!checkType(TokenType::RIGHTPAREN)) {
            throw runtime_error("Expected ')' after expression");
        }
        next();
        return expr;
    }

    throw runtime_error("Unexpected element in primary expression");

}
