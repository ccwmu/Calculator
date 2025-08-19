#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "Node.h"
#include <memory>

class NumberNode : public Node {
public:
    NumberNode(double value) : value(value) {}
    double evaluate(const std::map<std::string, double>& variables) const override { return value; }
    Node* clone() const override {
        return new NumberNode(value);
    }
private:
    double value;
};

#endif // NUMBERNODE_H