/** 
 * @file BinaryOpNode.h
 * @brief Binary operation nodes for the AST
 * @author Ethan Ye
 * @date 2025-8-20
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
    unique_ptr<Node> child1; /// < Left operand
    unique_ptr<Node> child2; /// < Right operand

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


class SubtractNode : public Node {
private: 
    unique_ptr<Node> child1;
    unique_ptr<Node> child2;

public: 
    SubtractNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : child1(move(left)), child2(move(right)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return child1->evaluate(variables) - child2->evaluate(variables);
    }
    Node* clone() const override {
        return new SubtractNode(unique_ptr<Node>(child1->clone()), unique_ptr<Node>(child2->clone()));
    }
};

class MultiplyNode : public Node {
private:
    unique_ptr<Node> child1;
    unique_ptr<Node> child2;

public:
    MultiplyNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : child1(move(left)), child2(move(right)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return child1->evaluate(variables) * child2->evaluate(variables);
    }
    Node* clone() const override {
        return new MultiplyNode(unique_ptr<Node>(child1->clone()), unique_ptr<Node>(child2->clone()));
    }
};

class DivideNode : public Node {
private:
    unique_ptr<Node> numerator;
    unique_ptr<Node> denominator;

public:
    DivideNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : numerator(move(left)), denominator(move(right)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        long double denom = denominator->evaluate(variables);
        if (denom == 0) {
            throw runtime_error("Division by zero error");
        }
        return numerator->evaluate(variables) / denom;
    }
    Node* clone() const override {
        return new DivideNode(unique_ptr<Node>(numerator->clone()), unique_ptr<Node>(denominator->clone()));
    }
};

class PowerNode : public Node {
private:
    unique_ptr<Node> base;
    unique_ptr<Node> exponent;

public:
    PowerNode(unique_ptr<Node> base, unique_ptr<Node> exponent)
        : base(move(base)), exponent(move(exponent)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        if (base->evaluate(variables) < 0 && exponent->evaluate(variables) != floor(exponent->evaluate(variables))) {
            throw runtime_error("negative base with non-integer exponent");
        }
        return pow(base->evaluate(variables), exponent->evaluate(variables));
    }
    Node* clone() const override {
        return new PowerNode(unique_ptr<Node>(base->clone()), unique_ptr<Node>(exponent->clone()));
    }
};

#endif // BINARYOPNODE_H