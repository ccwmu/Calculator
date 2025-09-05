/**
 * @file UnaryOpNode.h
 * @brief Unary operation nodes for the AST
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * This header defines all unary (single operand) mathematical operation 
 * nodes for the AST. Operations included are negation and absolute value.
*/

#ifndef UNARYOPNODE_H
#define UNARYOPNODE_H

#include "Node.h"

#include <memory>
#include <map>
#include <string>

/**
 * @class NegateNode
 * @brief Node representing a negation operation
 * 
 * Evaluates the negation of its child node
 */

class NegateNode : public Node {
private: 
    std::unique_ptr<Node> child; ///<Operand

public:

    /**
     * @brief Construct a new NegateNode
     * @param operand Operand to negate
	 */
    NegateNode(std::unique_ptr<Node> operand)
        : child(std::move(operand)) {}

	/**
    * @brief Evaluate the negation operation
	* @param variables std::map of variable names to values
	* @return Negated value of child node
    */ 
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return -child->evaluate(variables);
    }

	/**
	* @brief Creates a deep copy of the node
	* @return Pointer to a cloned new NegateNode
    */ 
    Node* clone() const override {
        return new NegateNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class AbsNode
 * @brief Node representing an absolute value operation
 * 
 * Evaluates the absolute value of its child node
*/

class AbsNode : public Node {
private:
	std::unique_ptr<Node> child; ///< Operand

public: 

    /**
     * @brief Construct a new AbsNode
	 * @param operand Operand to take absolute value of
    */
    AbsNode(std::unique_ptr<Node> operand) : child(std::move(operand)) {}

    /**
	* @brief Evaluate the absolute value operation
	* @param variables std::map of variable names to values 
	* @return Absolute value of child node
    */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return abs(child->evaluate(variables));
    }

    /**
	* @brief Creates a deep copy of the node
	* @return Pointer to a cloned new AbsNode
    */
    Node* clone() const override {
        return new AbsNode(std::unique_ptr<Node>(child->clone()));
    }
};

class FactorialNode : public Node {
private: 
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Consruct a new FactorialNode
	 * @param operand Operand to take factorial of
    */
    FactorialNode(std::unique_ptr<Node> operand) : child(std::move(operand)) {}

    /**
     * @brief Evaluate the factorial operation
     * @param variables std::map of variable names to values
     * @return Factorial of value of chile node
     * @throws runtime_error if child evaluates to negative number
    */
    long double evaluate(const std::map<std::string, long double>& variables) const override {

        if (child->evaluate(variables) < 0) { throw std::runtime_error("cannot take factorial of negative number"); }

        long double result = 1;
        for (int i = 1; i <= static_cast<int>(child->evaluate(variables)); ++i) {
            result *= i;
		}

        return result;
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a new cloned FactorialNode
    */
    Node* clone() const override {
		return new FactorialNode(std::unique_ptr<Node>(child->clone()));
    }
};

#endif // UNARYOPNODE_H