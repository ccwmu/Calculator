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

using namespace std;

/**
 * @class NegateNode
 * @brief Node representing a negation operation
 * 
 * Evaluates the negation of its child node
 */

class NegateNode : public Node {
private: 
    unique_ptr<Node> child; ///<Operand

public:

    /**
     * @brief Construct a new NegateNode
     * @param operand Operand to negate
	 */
    NegateNode(unique_ptr<Node> operand)
        : child(move(operand)) {}

	/**
    * @brief Evaluate the negation operation
	* @param variables Map of variable names to values
	* @return Negated value of child node
    */ 
    long double evaluate(const map<string, long double>& variables) const override {
        return -child->evaluate(variables);
    }

	/**
	* @brief Creates a deep copy of the node
	* @return Pointer to a cloned new NegateNode
    */ 
    Node* clone() const override {
        return new NegateNode(unique_ptr<Node>(child->clone()));
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
	unique_ptr<Node> child; ///< Operand

public: 

    /**
     * @brief Construct a new AbsNode
	 * @param operand Operand to take absolute value of
    */
    AbsNode(unique_ptr<Node> operand) : child(move(operand)) {}

    /**
	* @brief Evaluate the absolute value operation
	* @param variables Map of variable names to values 
	* @return Absolute value of child node
    */
    long double evaluate(const map<string, long double>& variables) const override {
        return abs(child->evaluate(variables));
    }

    /**
	* @brief Creates a deep copy of the node
	* @return Pointer to a cloned new AbsNode
    */
    Node* clone() const override {
        return new AbsNode(unique_ptr<Node>(child->clone()));
    }
};

#endif // UNARYOPNODE_H