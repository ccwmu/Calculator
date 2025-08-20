#ifndef BINARYOPNODE_H
#define BINARYOPNODE_H

#include <cmath>
#include <stdexcept>
#include "Node.h"

using namespace std;

// List of operations: 
// Add, Subtract, Multiply, Divide, Power

class AddNode : public Node {
private: 
    unique_ptr<Node> child1;
    unique_ptr<Node> child2;

public: 
    AddNode(unique_ptr<Node> left, unique_ptr<Node> right)
        : child1(move(left)), child2(move(right)) {}

    double evaluate(const map<string, double>& variables) const override {
        return child1->evaluate(variables) + child2->evaluate(variables);
    }
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
        double denom = denominator->evaluate(variables);
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

    double evaluate(const map<string, double>& variables) const override {
        if (base->evaluate(variables) < 0 && exponent->evaluate(variables) != floor(exponent->evaluate(variables))) {
            throw runtime_error("Invalid operation: negative base with non-integer exponent");
        }
        return pow(base->evaluate(variables), exponent->evaluate(variables));
    }
    Node* clone() const override {
        return new PowerNode(unique_ptr<Node>(base->clone()), unique_ptr<Node>(exponent->clone()));
    }
};

#endif // BINARYOPNODE_H