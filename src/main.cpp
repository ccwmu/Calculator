#include <iostream>
#include "Calculator.h"
#include "Lexicography.h"
#include "Node.h"
#include "FuncNode.h"
#include "BinaryOpNode.h"
#include "VariableNode.h"
#include "UnaryOpNode.h"
#include "NumberNode.h"
#include "Parser.h"

using namespace std;

const string HELP_MESSAGE = "coming soon";

int main() {
    Calculator calc;
    string input;

    cout << "Calculator (in development)" << endl;
    cout << "Type 'help' for assistance." << endl;

    while (true) {
        cout << ">>> ";
        getline(cin, input);
        if (input.empty()) continue;
        if (input == "exit") break;
        if (input == "help") { cout << HELP_MESSAGE << endl; continue; }
        if (input == "vars") { calc.printVars(); continue; }
        // Process input
        try {
            vector<Token> tokens = tokenize(input);
            //cout << "Tokens: ";
            //for (const auto& token : tokens) {
                //cout << "[" << token.value << "] ";
            //}
            //cout << endl;
            Parser parser(tokens);
            unique_ptr<Node> expression = parser.parse();
            
            if (parser.isAssignment()) {
                //cout << "variable" << endl;
                string varName = parser.getAssignVar();
                double result = calc.evaluate(move(expression));
                calc.assign(varName, result);
                cout << varName << " = " << result << endl;
            } else {
                
                double result = calc.evaluate(move(expression));
                cout << input << " = " << result << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}


