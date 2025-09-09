/**
 * @file Parser.cpp
 * @brief Implementation of parser class
 * @author Ethan Ye
 * @date 2025-8-19
*/

/*
This file uses recursive descent parsing to implement a hierarchical parsing structure.
It uses a top-down approach to parse dynamic arrays of tokens into an AST that will return the 
final result of the expression. It uses a series of parsing functions, each calling one that 
takes more priority over itself, enabling clean order of operations. 

Flow:
1. Start assignment operators (if no assignment, then continue to step 2)
    - if there is an assignment operator, parse the right-hand side expression (variable assignment happens in main loop)
2. Parse addition/subtraction
    - continue parsing the left side of the operator by parsing multiplication
    - since later functions don't parse addition/subtraction, they will stop parsing at the + or - token and return a tree, which is when the right side starts
    - then parse the right side
    - if right side contains another addition/subtraction, the now parsed expression before the + or - token will be used as the left side
3. Parse multiplication/division
    - continue parsing the left side of the operator by parsing power
    - like addition, parsing will stop at a * or / token and return a tree, which is when right side starts
    - then parse the right side, and like addition/subtraction, the right and left side combined will serve as the left side if another * or / token is found
4. Parse power
    - this case is special. since power is right associative unlike addition/multiplication, we need to parse the right side first
    - however, we will still continue to parse the left side, which might contain parenthesis, unary operators, or functions
    - then we parse the right side as another power expression, for cases like 2^(3+1)^4. This ensures that (3+1)^4 is parsed first, then 2^[(3+1)^4].
    - once no more ^ tokens are found, then continue parsing
5. Parse unary
    - not except for factorial, just trying to find a - token before a number, variable, or parenthesis
    - if found, create a negate node with the parsed unary expression as its child
    - if not found, then continue parsing primary
    - after parsePrimary is called, check for factorials, which are postfix unary operators
        - if found, create a factorial node with the parsed primary expression as its child
        - continue checking for more factorials until none are found using while
6. Parse primary
	- this is the case that takes the most hierarchy. It includes numbers, variables, functions, and grouping operators: (x) and |x|
    - it uses checkType() to determine what the current token is and parse accordingly
    - simplest case: number or variable
    - an absolute value operator | is treated like a function, where we parse the expression inside and expect another | to close it.
        - if | not found then throw runtime error
    - if function token is found then expect a left parenthesis
        - if function is a log, parse expression then expect a comma, if not then throw runtime error
        - if function is not a log, parse expression 
        - create a function node with the corresponding function name and the parsed expression as its child.
        - expect a right parenthesis to close the function call, if not then throw runtime error
    - if left parenthesis is found, parse the expression inside and expect a right parenthesis to close it, if not then throw runtime error
    - if none of the above cases are met, then throw runtime error
7. Parse preserve variable and remove variable
    - this is an oddball case. It is technically not part of the expression parsing, but it is easier to handle here because the lexer already tokenizes it
    and I don't want to handle tokens in main.
    - it the first token is a PRESERVE or REMOVE token, then expect the second token to be a variable and nothing else
    - if the syntax is correct then return true indicating that the user input is a preserve/remove command
    - if syntax is incorrect then throw runtime error

Example:

A sample input would be x = sin(3.14159/2) + 5^2 * |-3|
Lexicography would parse this into the following tokens:
[VARIABLE, x], [ASSIGN, =], [FUNCTION, sin], [LEFTPAREN, (], [NUMBER, 3.14159], [DIVIDE, /], [NUMBER, 2], [RIGHTPAREN, )], [PLUS, +], [NUMBER, 5], [POWER, ^],
[NUMBER, 2], [MULTIPLY, *], [ABS, |], [MINUS, -], [NUMBER, 3], [ABS, |]
The parser would then parse this into the following AST:

          AssignNode
         /          \
   VariableNode    AddNode
      (x)        /        \
              SinNode    MultiplyNode
               |         /           \
           DivideNode   PowerNode    AbsNode
           /     \     /        \          \
      Number(3.14159) /     Number(5)     NegateNode
                   Number(2)                  \
                                         Number(3)

The main loop would then evaluate this AST from the bottom up. Due to the order the parsing functions are called, the tree is structured so that high
priority operations are lower, so they are evaluated first. Then the result is returned to the top, where the assignment node would assign the final result to
the variable x. If there were no assignment and the input was just sin(3.14159/2) + 5^2 * |-3|, then the entry of the tree would just be the first AddNode, and
the final result would be returned directly to the main function.
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
#include <algorithm>


// Constructor, initializes tokens and current index to 0
Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), currIndex(0) {}

// Helper functions to navigate tokens

// Increments to previous token if possible and return it, otherwise return current token
Token& Parser::prev() {
    if (currIndex > 0) { return tokens[--currIndex]; }
    return tokens[currIndex];
}

// Returns current token
Token& Parser::curr() {
    return tokens[currIndex];
}

// Increments to next token if possible and return it, otherwise return current token
Token& Parser::next() {
    if (currIndex < tokens.size()-1) { return tokens[++currIndex]; }
    return tokens[currIndex];
}

// Checks if current token matches given type
bool Parser::checkType(const TokenType type) {
    return curr().type == type;
}

// Public parse function, serves as entry point for main
std::unique_ptr<Node> Parser::parse(){
    return parseExpression();
}

// Begin private parsing functions

// Entry point for parsing expressions
std::unique_ptr<Node> Parser::parseExpression(){
    return parseAssignment();
}

// Parses assignment expressions of the form variable = expression
std::unique_ptr<Node> Parser::parseAssignment() {
    if (Parser::isAssignment()) { 
        if (currIndex + 1 < tokens.size() &&                   // Ensure that input follows correct assignment syntax
            tokens[currIndex].type == TokenType::VARIABLE &&
            tokens[currIndex + 1].type == TokenType::ASSIGN) { 
            assignmentVar = tokens[currIndex].value;
            currIndex += 2;
            return parseAddition(); // Parse the expression on the right side of the assignment, which can include all other types of expressions
        }
        else { throw std::runtime_error("use [variable] = [expression] for assignment"); } // invalid assignment syntax
    }
    return parseAddition(); // if there is no assignment, then continue parsing.
}

std::unique_ptr<Node> Parser::parseAddition() { 
    std::unique_ptr<Node> left = parseMultiplication(); // continue parsing left side
    while (checkType(TokenType::PLUS) || checkType(TokenType::MINUS)) { // if there is a minus or a plus
		const TokenType op = curr().type; // plus/minus operator
        next(); // std::move to next token
        std::unique_ptr<Node> right = parseMultiplication(); // parse right side

        // left = (op == TokenType::PLUS) ? 
        //     std::make_unique<AddNode>(std::move(left), std::move(right)) : 
        //     std::make_unique<SubtractNode>(std::move(left), std::move(right));
        if (op == TokenType::PLUS) { left = std::make_unique<AddNode>(std::move(left), std::move(right)); } // make addition node from the left and right sides of the operator
        else { left = std::make_unique<SubtractNode>(std::move(left), std::move(right)); } // make subtraction node from the left and right sides of the operator

    }
    return left; // return the left side which now contains the rest of the expression tree
}

std::unique_ptr<Node> Parser::parseMultiplication() {
    std::unique_ptr<Node> left = parsePower(); // continue parsing left side
	while (checkType(TokenType::MULTIPLY) || checkType(TokenType::DIVIDE)) { // if there is a multiply or divide
		const TokenType op = curr().type; // multiply/divide operator
		next(); // std::move to next token
        std::unique_ptr<Node> right = parsePower(); // continue parse right side

        // left = (op == TokenType::MULTIPLY) ? 
        //     std::make_unique<MultiplyNode>(std::move(left), std::move(right)) : 
        //     std::make_unique<DivideNode>(std::move(left), std::move(right));

		if (op == TokenType::MULTIPLY) { left = std::make_unique<MultiplyNode>(std::move(left), std::move(right)); } // make multiplication node from the left and right sides of the operator
		else { left = std::make_unique<DivideNode>(std::move(left), std::move(right)); } // make division node from the left and right sides of the operator

    }
    return left;
}

std::unique_ptr<Node> Parser::parsePower() { // right associative
	std::unique_ptr<Node> left = parseUnary(); // continue parsing left side 
    if (checkType(TokenType::POWER)) { 
        next();
        std::unique_ptr<Node> right = parseUnary(); // parse right side (right-associative)

        return std::make_unique<PowerNode>(std::move(left), std::move(right)); // make power node from left and right sides
    }
    return left;
}

std::unique_ptr<Node> Parser::parseUnary() {
    std::unique_ptr<Node> node;
    if (checkType(TokenType::MINUS)) { 
        next();
		node = std::make_unique<NegateNode>(parseUnary()); // make negate node with the expression after as its child; call parseUnary again to handle cases like --sin(x)
    }
    else { node = parsePrimary(); } // continue parsing the rest of the expression

    // after parsePrimary is called check for factorials, which are postfix unary operators
    while (checkType(TokenType::FACTORIAL)) {
        next();
        node = std::make_unique<FactorialNode>(std::move(node));
    }

    return node;

}

std::unique_ptr<Node> Parser::parsePrimary() {
    // Numbers
    if (checkType(TokenType::NUMBER)) {
        long double value = stod(curr().value);
        next();
        return std::make_unique<NumberNode>(value);
    }

    // Vars

    if (checkType(TokenType::VARIABLE)) {
        std::string name = curr().value;
        next();
        return std::make_unique<VariableNode>(name);
    }

    // Absolute value

    if (checkType(TokenType::ABS)) {
        next();
        std::unique_ptr<Node> expr = parseExpression();
        if (!checkType(TokenType::ABS)) {
            throw std::runtime_error("expected closing | for absolute value expression");
        }
        next();
        return std::make_unique<AbsNode>(std::move(expr));
    }

    // Functions 

    if (checkType(TokenType::FUNCTION)) {
        const std::string funcName = curr().value;
        next();

        if (!checkType(TokenType::LEFTPAREN)) {
                throw std::runtime_error("expected '(' after function name");
            }
        next();
        if (funcName == "log" || funcName == "pow") {
            std::unique_ptr<Node> arg1 = parseExpression();
            if (!checkType(TokenType::COMMA)) {
                throw std::runtime_error("expected ',' between log arguments");
            }
            next();
            std::unique_ptr<Node> arg2 = parseExpression();

            if (!checkType(TokenType::RIGHTPAREN)) {
                throw std::runtime_error("expected ')' after function arguments");
            }
            next();
            
            if (funcName == "log") { return std::make_unique<LogNode>(std::move(arg1), std::move(arg2)); }
            if (funcName == "pow") { return std::make_unique<PowerNode>(std::move(arg1), std::move(arg2)); }
        }

        std::unique_ptr<Node> argument = parseExpression();

        if (!checkType(TokenType::RIGHTPAREN)) {
            throw std::runtime_error("expected ')' after function argument");
        }
        next();

        if (funcName == "sin") { return std::make_unique<SinNode>(std::move(argument)); }
        if (funcName == "cos") { return std::make_unique<CosNode>(std::move(argument)); }
        if (funcName == "tan") { return std::make_unique<TanNode>(std::move(argument)); }
        if (funcName == "asin") { return std::make_unique<ArcSinNode>(std::move(argument)); }
        if (funcName == "acos") { return std::make_unique<ArcCosNode>(std::move(argument)); }
        if (funcName == "atan") { return std::make_unique<ArcTanNode>(std::move(argument)); }
        if (funcName == "exp") { return std::make_unique<ExpNode>(std::move(argument)); }
        if (funcName == "ln") { return std::make_unique<LnNode>(std::move(argument)); }
        if (funcName == "log10") { return std::make_unique<LogTenNode>(std::move(argument)); }
        if (funcName == "sqrt") { return std::make_unique<SqrtNode>(std::move(argument)); }
        if (funcName == "abs") { return std::make_unique<AbsNode>(std::move(argument)); }
        if (funcName == "fact") { return std::make_unique<FactorialNode>(std::move(argument)); }

        throw std::runtime_error(funcName + " is not recognized as a variable, function, or operation");

    }

    if (checkType(TokenType::LEFTPAREN)) {
        next();
        std::unique_ptr<Node> expr = parseExpression();
        if (!checkType(TokenType::RIGHTPAREN)) {
            throw std::runtime_error("expected ')' after expression");
        }
        next();
        return expr;
    }

    throw std::runtime_error("unexpected element in expression");

}

bool Parser::parsePreserve() {
    if (tokens.size() == 3 && tokens[0].type == TokenType::PRESERVE && tokens[1].type == TokenType::VARIABLE) {
		assignmentVar = tokens[1].value;
        return true;
    }
    if (std::any_of(tokens.begin(), tokens.end(), [](const Token& t) { return t.type == TokenType::PRESERVE; })) {
        throw std::runtime_error("invalid preserve variable syntax! Use preserve [variable] to add a variable to preserved variables");
    }
    return false;
}

bool Parser::parseRemove() {
    if (tokens.size() == 3 && tokens[0].type == TokenType::REMOVE && tokens[1].type == TokenType::VARIABLE) {
		assignmentVar = tokens[1].value;
        return true;
    }
    if (std::any_of(tokens.begin(), tokens.end(), [](const Token& t) { return t.type == TokenType::REMOVE; })) {
        throw std::runtime_error("invalid remove variable syntax! Use remove [variable] to remove a variable from preserved variables");
    }
    return false;
}