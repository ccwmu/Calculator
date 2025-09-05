/** 
 * @file VariableNode.h
 * @brief Defines nodes representing variables in the AST
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * @details This header defines the VariableNode class which represents variables in the AST.
 * It includes methods to evaluate the variable's value based on a provided std::map of variable names to
 * values, and to clone the node.
*/


#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "Node.h"

#include <stdexcept>
#include <string>
#include <map>

/**
 * @class VariableNode
 * @brief Node representing a variable in the AST
 * 
 * Evaluates to the value of the variable from a provided std::map of variable names to values.
 * Throws an error if the variable is not found in the std::map.
 */
class VariableNode : public Node {
private:
    std::string name; ///< Name of the variable

public:

    /**
     * @brief Construct a new VariableNode
     * @param varName Name of the variable
	 */
    VariableNode(const std::string& varName)
        : name(varName) {}
    
	/**
	* @brief Evaluate the variable node by looking up the variable's value
	* @param variables std::map of variable names to their values
	* @return The value of the variable
	* @throws runtime_error if the variable is not found in the std::map
    */ 
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        throw std::runtime_error(name + " is not recognized as a variable, function, or operation");
    }

    /**
     * @brief Creates a deep copy of the VariableNode
     * @return Pointer to a cloned new VariableNode
	 */
    Node* clone() const override {
        return new VariableNode(name);
    }
};

#endif // VARIABLENODE_H

