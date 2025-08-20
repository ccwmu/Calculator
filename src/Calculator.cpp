#include <iostream>
#include "Calculator.h"
#include "Lexicography.h"
#include "Node.h"
#include "FuncNode.h"
#include "BinaryOpNode.h"
#include "VariableNode.h"
#include "UnaryOpNode.h"
#include "NumberNode.h"

using namespace std;

const string HELP_MESSAGE = "coming soon";


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
    throw runtime_error("Variable not found");
}

void Calculator::setVariable(const string& name, double value) {
    variables[name] = value;
}

int main() {
    Calculator calc;
    unique_ptr<Node> num1 = make_unique<NumberNode>(3.0);
    unique_ptr<Node> num2 = make_unique<NumberNode>(3.0);
    calc.assign("x", 3.0);
    

    unique_ptr<Node> sum = make_unique<MultiplyNode>(move(calc.getVariable("x")), move(num2));
    cout << calc.evaluate(move(sum)) << endl;
    calc.setVariable("x", 5.0);
    unique_ptr<Node> newSum = make_unique<MultiplyNode>(move(calc.getVariable("x")), move(num1));
    cout << calc.evaluate(move(newSum)) << endl;

    return 0;
}


