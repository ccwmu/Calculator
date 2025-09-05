/**
 * @file NumberNode.h
 * @brief Node representing a numeric constant in the AST
 * @author  Ethan Ye
 * @date 2025-8-18
 *
 * This header defines the NumberNode class which represents numeric constants in the
 * AST. It includes methods to evaluate the constant's value and to clone the node.
 *
*/

#pragma once

#include "Node.h"
#include <map>
#include <string>

/**
 * @class NumberNode
 * @brief Node representing a numeric constant in the AST
 *
 * Evaluates to the numeric value it represents.
 */
class NumberNode : public Node {
private:
    long double value; ///< Numeric value of the constant

public:

    /**
     * @brief Construct a new NumberNode
     * @param value Numeric value of the constant
     */
    NumberNode(long double value) : value(value) {}

    /**
     * @brief Evaluate the numeric constant
     * @param variables Map of variable names to values (not used in this node)
     * @return The numeric value of the constant
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override { return value; }

    /**
     * @brief Creates a deep copy of the NumberNode
     * @return Pointer to a cloned new NumberNode
     */
    Node* clone() const override {
        return new NumberNode(value);
    }
};
