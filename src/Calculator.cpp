#include "Calculator.h"
#include "VariableNode.h"
#include <iostream>

Calculator::Calculator() {
    variables = map<string, double>();
    varNodes = map<string, unique_ptr<Node>>();
}

double Calculator::evaluate(unique_ptr<Node> expression) {
    return expression->evaluate(variables);
}

void Calculator::assign(const string& name, double value) {
    variables[name] = value;
    varNodes[name] = make_unique<VariableNode>(name);
}

unique_ptr<Node> Calculator::getVariable(const string& name)  {
    auto thing = varNodes.find(name);
    if (thing != varNodes.end()) {
        return unique_ptr<Node>(thing->second->clone());
    }
    throw runtime_error("variable not found");
}

void Calculator::setVariable(const string& name, double value) {
    variables[name] = value;
}

void Calculator::printVars() const {
    for (const auto& pair : variables) {
        cout << pair.first << " = " << pair.second << endl;
    }
}

void Calculator::clear() {
    std::map<std::string, double> preserverValues = {
        {"pi", 3.141592653589793},
        {"e", 2.718281828459045},
        {"deg2rad", 3.141592653589793 / 180},
        {"rad2deg", 180 / 3.141592653589793}
    };
    variables.clear();
    varNodes.clear();
    for (const auto& pair : preserverValues) {
        assign(pair.first, pair.second);
    }
}