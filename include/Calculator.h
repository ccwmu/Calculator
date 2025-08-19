#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Node.h"
#include <stdexcept>
using namespace std;
class Calculator{
private:
    map<string, double> variables;
public:
    double evaluate(unique_ptr<Node> expression);

    double assign(const string& name, double value);

    double getVariable(const string& name) const;

    double setVariable(const string& name, double value);

    void printVars() const;
};

#endif //CALCULATOR_H