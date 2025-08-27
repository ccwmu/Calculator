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

#ifndef BINARYOPNODE_H
#define BINARYOPNODE_H

#include <cmath>
#include <stdexcept>
#include "Node.h"

using namespace std;

/**
 * @class AddNode
 * @brief Node representing an addition operation
 *
 * Evaluates the sum of two child nodes
 */

class AddNode : public Node {
private: 
    unique_ptr<Node> child1; ///< Left operand
    unique_ptr<Node> child2; ///< Right operand

public: 

    /**
     * @brief Construct a new AddNode
     * @param left Left operand
     * @param right Right operand
     */
    AddNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : child1(move(left)), child2(move(right)) {}

    /**
     * @brief Evaluate the addition operation
     * @param variables Map of variable names to values
     * @return Sum of left and right nodes
     */
    long double evaluate(const map<string, long double>& variables) const override {
        return child1->evaluate(variables) + child2->evaluate(variables);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new AddNode
     */
    Node* clone() const override {
        return new AddNode(unique_ptr<Node>(child1->clone()), unique_ptr<Node>(child2->clone()));
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
    unique_ptr<Node> child1; ///< Left operand
    unique_ptr<Node> child2; ///< Right operand

public: 

    /**
     * @brief Construct a new SubtractNode
     * @param left Left operand
     * @param right Right operand
     */
    SubtractNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : child1(move(left)), child2(move(right)) {}


    /**
     * @brief Evaluate the subtraction operation
     * @param variables Map of variable names to values
     * @return Difference of left and right nodes
     */
    long double evaluate(const map<string, long double>& variables) const override {
        return child1->evaluate(variables) - child2->evaluate(variables);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new SubtractNode
     */
    Node* clone() const override {
        return new SubtractNode(unique_ptr<Node>(child1->clone()), unique_ptr<Node>(child2->clone()));
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
    unique_ptr<Node> child1; ///< Left operand
    unique_ptr<Node> child2; ///< Right operand

public:

    /**
     * @brief Construct a new MultiplyNode
     * @param left Left operand
     * @param right Right operand
     */
    MultiplyNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : child1(move(left)), child2(move(right)) {}

    /**
     * @brief Evaluate the multiplication operation
     * @param variables Map of variable names to values
     * @return Product of left and right nodes
     */
    long double evaluate(const map<string, long double>& variables) const override {
        return child1->evaluate(variables) * child2->evaluate(variables);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new MultiplyNode
     */
    Node* clone() const override {
        return new MultiplyNode(unique_ptr<Node>(child1->clone()), unique_ptr<Node>(child2->clone()));
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
	unique_ptr<Node> numerator;   ///< Numerator operand
	unique_ptr<Node> denominator; ///< Denominator operand

public:

    /**
     * @brief Construct a new DivideNode
     * @param left Numerator operand
     * @param right Denominator operand
	 */ 
    DivideNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : numerator(move(left)), denominator(move(right)) {}

	/**
	* @brief Evaluate the division operation
	* @param variables Map of variable names to values
	* @return Quotient of numerator and denominator nodes
	* @throws runtime_error if division by zero occurs
    */ 
    long double evaluate(const map<string, long double>& variables) const override {
        long double denom = denominator->evaluate(variables);
        if (denom == 0) {
            throw runtime_error("division by zero");
        }
        return numerator->evaluate(variables) / denom;
    }

    /**
    * @brief Creates a deep copy of the node
	* @return Pointer to a cloned new DivideNode
    */
    Node* clone() const override {
        return new DivideNode(unique_ptr<Node>(numerator->clone()), unique_ptr<Node>(denominator->clone()));
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
    unique_ptr<Node> base;      ///< Base operand
    unique_ptr<Node> exponent;  ///< Exponent operand

public:

    /**
     * @brief Construct a new PowerNode
     * @param base Base operand
     * @param exponent Exponent operand
     */
    PowerNode(unique_ptr<Node> base, unique_ptr<Node> exponent)
        : base(move(base)), exponent(move(exponent)) {}

    /**
     * @brief Evaluate the power operation
     * @param variables Map of variable names to values
     * @return Result of raising the base to the exponent
	 * @throws runtime_error if base is negative and exponent is non-integer
     */
    long double evaluate(const map<string, long double>& variables) const override {
        if (base->evaluate(variables) < 0 && exponent->evaluate(variables) != floor(exponent->evaluate(variables))) {
            throw runtime_error("negative base with non-integer exponent");
        }
        return pow(base->evaluate(variables), exponent->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to a cloned new PowerNode
     */
    Node* clone() const override {
        return new PowerNode(unique_ptr<Node>(base->clone()), unique_ptr<Node>(exponent->clone()));
    }
};

#endif // BINARYOPNODE_H