#ifndef UNARYOPNODE_H
#define UNARYOPNODE_H

#include "Node.h"

using namespace std;

class NegateNode : public Node {
private: 
    unique_ptr<Node> child;

public:
    NegateNode(unique_ptr<Node> operand)
        : child(move(operand)) {}

    double evaluate(const map<string, double>& variables) const override {
        return -child->evaluate(variables);
    }
    Node* clone() const override {
        return new NegateNode(unique_ptr<Node>(child->clone()));
    }
};

class PlusNode : public Node {
private:
    unique_ptr<Node> child;

public:
    PlusNode(unique_ptr<Node> operand)
        : child(move(operand)) {}

    double evaluate(const map<string, double>& variables) const override {
        return child->evaluate(variables);
    }
    Node* clone() const override {
        return new PlusNode(unique_ptr<Node>(child->clone()));
    }
};

#endif // UNARYOPNODE_H