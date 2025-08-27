/**
 * @file Calculator.h
 * @brief Defines Calculator class for high-level evaluation and variable management
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * @details This header defines the Calculator class which declares functions
 * to evaluate mathematical expressions represented as ASTs,
 * as well as managing variables, their values, and the nodes corresponding to them.
 * It also includes functions that format numbers and print tokens in a certain way for
 * better result statements.
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Node.h"
#include "Lexicography.h"
#include <stdexcept>
#include <set>

using namespace std;

/**
 * @class Calculator
 * @brief The main higher-level engine for evaluating expressions, managing vars, and formatting output
 * 
 * This class declares functions to evaluate expressions represented as ASTs, add, get, and set variables, 
 * and format outputs. It also includes Maps to store variable names, their nodes, and their values, and 
 * functions to format output.
 */ 
class Calculator{
private:
	map<string, long double> variables; ///< Map of variable names to their values
	map<string, unique_ptr<Node>> varNodes; ///< Map of variable names to their corresponding AST nodes
	set<string> preservedValues = {  ///< Predefined constants
		"pi", "e", "deg2rad", "rad2deg"
	};

public:

    /**
	* @brief Construct a new Calculator object
	* @details Initializes Maps that store variables, their corresponding nodes on the AST, and their
    * values, as well as predefines the variables: pi, e, deg2rad, rad2deg
    */
    Calculator();

	/**
	* @brief Evaluates a mathematical expression represented as an AST
	* @param expression A unique pointer to the root node of the AST representing the expression
	* @return The result of evaluating the expression as a long double
    */ 
    long double evaluate(unique_ptr<Node> expression);
    
	/**
	* @brief Assigns a value to a variable and creates its corresponding AST node
	* @param name The name of the variable to assign
	* @param value The value to assign to the variable
    */ 
    void assign(const string& name, long double value);

    /**
	* @brief Retrieves the AST node corresponding to a variable
	* @param The name of the variable to retrieve
	* @return A unique pointer to the AST node representing the variable
	* @throws runtime_error if the variable does not exist
    */ 
    unique_ptr<Node> getVariable(const string& name) ;

	/**
	* @brief Updates the value of an existing variable
	* @param name The name of the variable to update
	* @param value The new value to assign to the variable
	*/
    void setVariable(const string& name, long double value);

	/**
	* @brief Prints all currently defined variables and their values to the console
	*/ 
    void printVars() const;

	/**
	* @brief Clears all user-defined variables while preserving predefined constants
	* @param toPreserve A map of variable names to values to preserve
	*/ 
    void clear();

	/**
	* @brief Formats a list of tokens into a human-readable and spaced string
	* @param tokens A vector of Token objects to format
	* @return A formatted string representation of the tokens
	*/ 
    string printTokens(vector<Token> tokens);

	/**
	* @brief Formats a long double into a string, removing unnecessary trailing zeros
	* @param value The long double value to format
	* @return A string representation of the number without trailing zeros.
	*/ 
	string formatNumber(long double value);

	/**
	 * @brief Gets the map of preserved variable names to values
	 * @return The map of preserved variable names to values
	 */
	set<string> getPreservedValues() const { return preservedValues; }

	/**
	 * @brief Adds a variable name to the list of preserved variables
	 * @param name The name of the var to preserve
	*/
	void addPreservedValue(const string& name);

	/**
	 * @brief Removes a variable name from the list of preserved variables
	 * @param name The name of the var to remove from preserved list
	*/
	void removePreservedValue(const string& name);

};

#endif //CALCULATOR_H