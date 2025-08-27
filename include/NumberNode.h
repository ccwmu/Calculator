/**
 * 
*/


#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "Node.h"
#include <memory>

class NumberNode : public Node {
public:
    NumberNode(long double value) : value(value) {}
    long double evaluate(const std::map<std::string, long double>& variables) const override { return value; }
    Node* clone() const override {
        return new NumberNode(value);
    }
private:
    long double value;
};

#endif // NUMBERNODE_H