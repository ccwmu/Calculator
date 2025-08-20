#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Node.h"
#include <stdexcept>
using namespace std;
class Calculator{
private:
    map<string, double> variables;
    map<string, unique_ptr<Node>> varNodes;
public:
    Calculator();
    double evaluate(unique_ptr<Node> expression);

    void assign(const string& name, double value);

    unique_ptr<Node> getVariable(const string& name) ;

    void setVariable(const string& name, double value);
    void printVars() const;
};

#endif //CALCULATOR_H