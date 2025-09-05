/** 
 * @file BinaryOpNode.h
 * @brief Binary operation nodes for the AST
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * This header defines all binary (two-operand) mathematical operation
 * nodes for the AST. Operations are addition, subtraction, multiplication,
 * division, and exponentiation.
 */

#pragma once

#include "Node.h"

#include <cmath>
#include <memory>
#include <map>
#include <stdexcept>
#include <string>

/**
 * @class AddNode
 * @brief Node representing an addition operation
 *
 * Evaluates the sum of two child nodes
 */

class AddNode : public Node {
private: 
    std::unique_ptr<Node> child1; ///< Left operand
    std::unique_ptr<Node> child2; ///< Right operand

public: 

    /**
     * @brief Construct a new AddNode
     * @param left Left operand
     * @param right Right operand
     */
    AddNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : child1(std::move(left)), child2(std::move(right)) {}

    /**
     * @brief Evaluate the addition operation
     * @param variables std::map of variable names to values
     * @return Sum of left and right nodes
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return child1->evaluate(variables) + child2->evaluate(variables);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new AddNode
     */
    Node* clone() const override {
        return new AddNode(std::unique_ptr<Node>(child1->clone()), std::unique_ptr<Node>(child2->clone()));
    }
};

/**
* @class SubtractNode
* @brief Node representing a subtraction operation
* 
* Evaluates difference of two child nodes
*/

class SubtractNode : public Node {
private: 
    std::unique_ptr<Node> child1; ///< Left operand
    std::unique_ptr<Node> child2; ///< Right operand

public: 

    /**
     * @brief Construct a new SubtractNode
     * @param left Left operand
     * @param right Right operand
     */
    SubtractNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : child1(std::move(left)), child2(std::move(right)) {}


    /**
     * @brief Evaluate the subtraction operation
     * @param variables std::map of variable names to values
     * @return Difference of left and right nodes
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return child1->evaluate(variables) - child2->evaluate(variables);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new SubtractNode
     */
    Node* clone() const override {
        return new SubtractNode(std::unique_ptr<Node>(child1->clone()), std::unique_ptr<Node>(child2->clone()));
    }
};

/**
 * @class MultiplyNode
 * @brief Node representing a multiplication operation
 *
 * Evaluates the product of two child nodes
 */
class MultiplyNode : public Node {
private:
    std::unique_ptr<Node> child1; ///< Left operand
    std::unique_ptr<Node> child2; ///< Right operand

public:

    /**
     * @brief Construct a new MultiplyNode
     * @param left Left operand
     * @param right Right operand
     */
    MultiplyNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : child1(std::move(left)), child2(std::move(right)) {}

    /**
     * @brief Evaluate the multiplication operation
     * @param variables std::map of variable names to values
     * @return Product of left and right nodes
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return child1->evaluate(variables) * child2->evaluate(variables);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new MultiplyNode
     */
    Node* clone() const override {
        return new MultiplyNode(std::unique_ptr<Node>(child1->clone()), std::unique_ptr<Node>(child2->clone()));
    }
};

/**
 * @class DivideNode
 * @brief Node representing a division operation
 *
 * Evaluates the quotient of two child nodes
 */
class DivideNode : public Node {
private:
	std::unique_ptr<Node> numerator;   ///< Numerator operand
	std::unique_ptr<Node> denominator; ///< Denominator operand

public:

    /**
     * @brief Construct a new DivideNode
     * @param left Numerator operand
     * @param right Denominator operand
	 */ 
    DivideNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : numerator(std::move(left)), denominator(std::move(right)) {}

	/**
	* @brief Evaluate the division operation
	* @param variables std::map of variable names to values
	* @return Quotient of numerator and denominator nodes
	* @throws runtime_error if division by zero occurs
    */ 
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        long double denom = denominator->evaluate(variables);
        if (denom == 0) {
            throw std::runtime_error("division by zero");
        }
        return numerator->evaluate(variables) / denom;
    }

    /**
    * @brief Creates a deep copy of the node
	* @return Pointer to a cloned new DivideNode
    */
    Node* clone() const override {
        return new DivideNode(std::unique_ptr<Node>(numerator->clone()), std::unique_ptr<Node>(denominator->clone()));
    }
};

/**
 * @class PowerNode
 * @brief Node representing a power operation
 *
 * Evaluates the result of raising a base to an exponent
 */
class PowerNode : public Node {
private:
    std::unique_ptr<Node> base;      ///< Base operand
    std::unique_ptr<Node> exponent;  ///< Exponent operand

public:

    /**
     * @brief Construct a new PowerNode
     * @param base Base operand
     * @param exponent Exponent operand
     */
    PowerNode(std::unique_ptr<Node> base, std::unique_ptr<Node> exponent)
        : base(std::move(base)), exponent(std::move(exponent)) {}

    /**
     * @brief Evaluate the power operation
     * @param variables std::map of variable names to values
     * @return Result of raising the base to the exponent
	 * @throws runtime_error if base is negative and exponent is non-integer
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        if (base->evaluate(variables) < 0 && exponent->evaluate(variables) != floor(exponent->evaluate(variables))) {
            throw std::runtime_error("negative base with non-integer exponent");
        }
        return pow(base->evaluate(variables), exponent->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new PowerNode
     */
    Node* clone() const override {
        return new PowerNode(std::unique_ptr<Node>(base->clone()), std::unique_ptr<Node>(exponent->clone()));
    }
};
