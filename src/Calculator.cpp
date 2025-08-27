#include "Calculator.h"
#include "VariableNode.h"
#include <iostream>

Calculator::Calculator() {
    variables = map<string, long double>();
    varNodes = map<string, unique_ptr<Node>>();
    // Predefined variables
	assign("pi", 3.141592653589793);
	assign("e", 2.718281828459045);
	assign("deg2rad", 3.141592653589793 / 180);
	assign("rad2deg", 180 / 3.141592653589793);

    addPreservedValue("pi");
    addPreservedValue("e");
    addPreservedValue("deg2rad");
    addPreservedValue("rad2deg");
}

long double Calculator::evaluate(unique_ptr<Node> expression) {
    return expression->evaluate(variables);
}

void Calculator::assign(const string& name, long double value) {
    variables[name] = value;
    varNodes[name] = make_unique<VariableNode>(name);
}

unique_ptr<Node> Calculator::getVariable(const string& name)  {
    auto thing = varNodes.find(name);
    if (thing != varNodes.end()) {
        return unique_ptr<Node>(thing->second->clone());
    }
    throw runtime_error("variable not found");
}

void Calculator::setVariable(const string& name, long double value) {
    variables[name] = value;
}

void Calculator::printVars() const {
    for (const auto& pair : variables) {
        cout << pair.first << " = " << pair.second << endl;
    }
}

void Calculator::clear() {
	map<string, long double> preservedVars;
    for (const auto& name : preservedValues) {
        auto it = variables.find(name);
        if (it != variables.end()) {
            preservedVars[name] = it->second;
        }
    }
	
    variables.clear();
    varNodes.clear();

    for (const auto& pair : preservedVars) {
		assign(pair.first, pair.second);
    }
}

std::string Calculator::formatNumber(long double value) {
    std::string str = std::to_string(value);
    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    // If the last character is a decimal point, remove it
    if (!str.empty() && str.back() == '.') {
        str.pop_back();
    }
    return str;
}


void Calculator::addPreservedValue(const std::string& name) {
    if (variables.find(name) == variables.end()) {
		throw std::runtime_error("variable " + name + " does not exist and cannot be preserved.");
	}
	preservedValues.insert(name);
}

void Calculator::removePreservedValue(const std::string& name) {
    preservedValues.erase(name);
}

std::string Calculator::printTokens(std::vector<Token> tokens)
{
    std::string result = "";
    //not to be confused with a debug function
    TokenType prevType = TokenType::END;
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
                prevType = token.type;
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
                prevType = token.type;
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
        prevType = token.type;
        
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