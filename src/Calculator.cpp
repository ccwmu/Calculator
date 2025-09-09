/**
 * @file Calculator.cpp
 * @brief Implementation of the Calculator class for evaluating mathematical expressions.
 * @author Ethan Ye
 * @date 2025-8-18
 *
 * This file contains the implementation of the Calculator class, which provides methods to
 * evaluate mathematical expressions represented as abstract syntax trees (ASTs). It supports
 * variable assignment, predefined constants, and formatting of numerical results.
 *
 */

#include "Calculator.h"
#include "VariableNode.h"

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

Calculator::Calculator() {

    // Variables and their corresponding nodes
    variables = std::map<std::string, long double>();
    varNodes = std::map<std::string, std::unique_ptr<Node>>();

    // Predefined variables
	assign("pi", 3.141592653589793);
	assign("e", 2.718281828459045);
	assign("deg2rad", 3.141592653589793 / 180);
	assign("rad2deg", 180 / 3.141592653589793);

    // Preserved variables
    addPreservedValue("pi");
    addPreservedValue("e");
    addPreservedValue("deg2rad");
    addPreservedValue("rad2deg");
}

// Evaluates the given expression node and returns the result
long double Calculator::evaluate(const std::unique_ptr<Node>& expression) const {
    return expression->evaluate(variables);
}

// Assigns a value to a variable and creates its corresponding VariableNode
void Calculator::assign(const std::string& name, const long double value) {
    variables[name] = value;
    varNodes[name] = std::make_unique<VariableNode>(name);
}

// Retrieves a clone of the VariableNode for the given variable name
std::unique_ptr<Node> Calculator::getVariable(const std::string& name)  {
    if (const auto thing = varNodes.find(name); thing != varNodes.end()) {
        return std::unique_ptr<Node>(thing->second->clone());
    }
    throw std::runtime_error("variable not found");
}

// Sets the value of an existing variable
void Calculator::setVariable(const std::string& name, const long double value) {
    variables[name] = value;
}

// Prints all variables and their values
void Calculator::printVars() const {
    for (const auto&[fst, snd] : variables) {
        std::cout << fst << " = " << snd << std::endl;
    }
}

// Clears all variables except those that are preserved
void Calculator::clear() {
	std::map<std::string, long double> preservedVars;
    for (const auto& name : preservedValues) {
        if (auto it = variables.find(name); it != variables.end()) {
            preservedVars[name] = it->second;
        }
    }
	
    variables.clear();
    varNodes.clear();

    for (const auto&[fst, snd] : preservedVars) {
		assign(fst, snd);
    }
}

// Formats a long double to a string, removing unnecessary trailing zeros
std::string Calculator::formatNumber(const long double value) {
    std::string str = std::to_string(value);
    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    // If the last character is a decimal point, remove it
    if (!str.empty() && str.back() == '.') {
        str.pop_back();
    }
    return str;
}

// Adds a variable to the set of preserved values
void Calculator::addPreservedValue(const std::string& name) {
    if (variables.find(name) == variables.end()) {
		throw std::runtime_error("variable " + name + " does not exist and cannot be preserved.");
	}
	preservedValues.insert(name);
}

// Removes a variable from the set of preserved values
void Calculator::removePreservedValue(const std::string& name) {
    preservedValues.erase(name);
}

// Formats and prints a list of tokens as a string
std::string Calculator::printTokens(const std::vector<Token>& tokens)
{
    std::string result;
    //not to be confused with a debug function
    size_t absCounter = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        // Skip end tokens
        if (token.type == TokenType::END) { continue; }

        // There are never spaces after left parenthesis or function names
        if (token.type == TokenType::LEFTPAREN || 
            token.type == TokenType::FUNCTION) { result += token.value; }
        
        // Handle number, where in some cases we want a space after and in some cases we don't
        if (token.type == TokenType::NUMBER) {
            result += formatNumber(stod(token.value)); 

            // The only cases where we don't want a space after a number is when there is a 
            // closing parenthesis or a comma right after
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::RIGHTPAREN ||
                i + 1 < tokens.size() && tokens[i + 1].type == TokenType::COMMA) {
                continue;
            }
            result += " ";
        }

        // Handle variables, where in some cases we want a space after and in some cases we don't
        if (token.type == TokenType::VARIABLE) {
            result += token.value;
            
            // Same as in number, we don't want a space if there is a closing paren or a comma.
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::RIGHTPAREN ||
                i + 1 < tokens.size() && tokens[i + 1].type == TokenType::COMMA) {
                continue;
            }
            result += " ";
        }

        // We always want spaces after operators, commas, and assignment operators
        if (token.type == TokenType::PLUS ||
            token.type == TokenType::MINUS ||
            token.type == TokenType::MULTIPLY ||
            token.type == TokenType::DIVIDE ||
            token.type == TokenType::POWER ||
            token.type == TokenType::COMMA ||
            token.type == TokenType::ASSIGN) {
            result += token.value + " ";
        }

        // Special case for absolute value ||
        // We don't want a space after the first absolute value, but we do want one after the second.
        if (token.type == TokenType::ABS) {

            // First absolute value - no space
            if (absCounter % 2 == 0) { result += token.value; } 

            // Second absolute value - add space
            else { result += token.value + " "; }
            absCounter++;
        }
        
        // Sometimes we want a space after right parenthesis, but sometimes we don't.
        if (token.type == TokenType::RIGHTPAREN) {
            result += token.value;
            if (i + 1 < tokens.size() && (tokens[i + 1].type == TokenType::ASSIGN || 
                tokens[i + 1].type == TokenType::END)) {
                result += " ";
			}

            // We want a space if the next token is an operator
            if (i + 1 < tokens.size() && (tokens[i + 1].type == TokenType::PLUS ||
                tokens[i + 1].type == TokenType::MINUS ||
                tokens[i + 1].type == TokenType::MULTIPLY ||
                tokens[i + 1].type == TokenType::DIVIDE ||
                tokens[i + 1].type == TokenType::POWER ||
                tokens[i + 1].type == TokenType::COMMA ||
                tokens[i + 1].type == TokenType::ASSIGN)) {
                result += " ";
            }
            
        }
    }
    return result;
}