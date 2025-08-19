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


class Calculator {
    void printVars() const {
        for (const auto& var : variables) {
            cout << var.first << " = " << var.second << endl;
        }
    }
}


int main() {
    string line;

    cout << "Type vars to see variables, exit to quit, and help for all supported functions" << endl;

    while (true) {
        cout << ">>> ";
        getline(cin, line);
        if (line == "vars") { printVars(); }
        if (line == "exit") { break; } 
        else if (line == "help") {
            cout << "Coming soon!" << endl;
        } 
        else if (line.empty()){ cout << 0 << endl; continue; }
        else { cout << "Unknown command: " << line << endl; }
    }

    return 0;
}


