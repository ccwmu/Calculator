#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Node.h"
#include "Lexicography.h"
#include <stdexcept>
using namespace std;
class Calculator{
private:
    map<string, long double> variables;
    map<string, unique_ptr<Node>> varNodes;
public:
    Calculator();
    long double evaluate(unique_ptr<Node> expression);

    void assign(const string& name, long double value);

    unique_ptr<Node> getVariable(const string& name) ;

    void setVariable(const string& name, long double value);
    void printVars() const;
    void clear();
    std::string printTokens(vector<Token> tokens);
	std::string formatNumber(long double value);
};

#endif //CALCULATOR_H