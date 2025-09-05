/**
 * @file Parser.h
 * @brief Header file for the Parser class that converts tokens into an AST.
 * @author Ethan Ye
 * @date 2025-8-18
 *
 * This file defines the Parser class, which takes a vector of tokens generated
 * by the lexer and constructs an Abstract Syntax Tree (AST) representing the
 * structure of the input expression. The parser supports various operations,
 * including addition, multiplication, exponentiation, unary operations, and
 * function calls. It also parses variable assignments but leaves the actual
 * assignment to be handled in the main loop.
 *
 */

#pragma once

#include "Lexicography.h"
#include "Node.h"

#include <memory>
#include <string>
#include <vector>

/**
 * @class Parser
 * @brief Parses a vector of tokens into an Abstract Syntax Tree (AST)
 *
 * The Parser class implements a recursive descent parser that converts a
 * sequence of tokens into an AST representing the structure of the input
 * expression. It supports various mathematical operations, functions, and
 * variable assignments.
 */
class Parser {
private:

    std::vector<Token> tokens;   ///< Vector of tokens to parse
    std::size_t currIndex;       ///< Current index in the loop
    bool containsNewVar = false; ///< Whether the expression contains a new variable assignment
    std::string assignmentVar;   ///< The variable being assigned to. Empty if no assignment.

    /* Helper functions for loop control */

    /**
     * @return the previous token in the vector if possible, otherwise the current token
     * This function also decrements currIndex if possible
     */
    Token& prev();

    /**
     * @return the current token in the vector
     */
    Token& curr();

    /**
     * @return the next token in the vector if possible, otherwise the current token
     * This function also increments currIndex if possible
     */
    Token& next();

    /**
     * @param type The token type to check against
     * @return true if the current token matches the given type, false otherwise
     */
    bool checkType(TokenType type);

    /* Parsing functions, ordered in descending levels of precedence */

    /**
     * @return A unique pointer to the root node of the whole parsed AST
     * This is the entry point for parsing expressions.
     */
    std::unique_ptr<Node> parseExpression();

    /**
     * @return A unique pointer to the root node of the parsed AST
     * This function handles parsing of assignment expressions.
     */
    std::unique_ptr<Node> parseAssignment();

    /**
     * @return A unique pointer to the root node of the parsed AST
     * This function handles parsing of addition and subtraction expressions.
     */
    std::unique_ptr<Node> parseAddition();

    /**
     * @return A unique pointer to the root node of the parsed AST
     * This function handles parsing of multiplication and division expressions.
     */
    std::unique_ptr<Node> parseMultiplication();

    /**
     * @return A unique pointer to the root node of the parsed AST
     * This function handles parsing of exponentiation expressions.
     */
    std::unique_ptr<Node> parsePower();

    /**
     * @return A unique pointer to the root node of the parsed AST
     * This function handles parsing of unary operations (e.g., negation).
     */
    std::unique_ptr<Node> parseUnary();

    /**
     * @return A unique pointer to the root node of the parsed AST
     * This function handles parsing of primary expressions, including numbers,
     * variables, function calls, and parenthesized expressions.
     */
    std::unique_ptr<Node> parsePrimary();

public:

    /**
     * @brief Construct a new Parser object
     * @param tokens Vector of tokens to parse
     */
    Parser(std::vector<Token> tokens);

    /**
     * @brief Public parse function that serves as the entry point for parsing
     * @return A unique pointer to the root node of the whole parsed AST
     */
    std::unique_ptr<Node> parse();

    /**
     * @brief Check if the parsed expression is an assignment
     * @return true if the expression is an assignment, false otherwise
     */
    bool isAssignment() const {
        for (const Token token : tokens) {
            if (token.type == TokenType::ASSIGN) { return true; }
		}
        return false;
    }

    /**
     * @brief Get the variable being assigned to
     * @return The variable name as a string, or an empty string if no assignment
     */
    std::string getAssignVar() const { return assignmentVar; }

    /**
     * @brief Parse preserve command
     * @return true if the command is valid, false otherwise
     * This function checks if the tokens represent a valid preserve command.
     */
    bool parsePreserve();

    /**
     * @brief Parse remove command
     * @return true if the command is valid, false otherwise
     * This function checks if the tokens represent a valid remove command.
     */
    bool parseRemove();
};

