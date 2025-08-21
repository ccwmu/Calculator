#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "Node.h"
#include <stdexcept>

using namespace std;

class VariableNode : public Node {
private:
    string name;

public:
    VariableNode(const string& varName)
        : name(varName) {}

    long double evaluate(const map<string, long double>& variables) const override {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        throw runtime_error("Undefined variable: " + name);
    }

    Node* clone() const override {
        return new VariableNode(name);
    }
};

#endif // VARIABLENODE_H

