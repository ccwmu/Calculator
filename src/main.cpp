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

const string HELP_MESSAGE = 
    "=== Calculator Help ===\n"
    "\n"
    "BASIC OPERATIONS:\n"
    "  +, -, *, /          Basic arithmetic\n"
    "  ^                   Exponentiation (2^3 = 8)\n"
    "  ( )                 Parentheses for grouping\n"
    "  | |                 Absolute value\n"
    "\n"
    "VARIABLES:\n"
    "  x = 5               Assign value to variable\n"
    "  y = x * 2 + 3       Use variables in expressions\n"
    "  vars                Show all variables\n"
    "\n"
    "FUNCTIONS:\n"
    "  sin(x), cos(x), tan(x)     Trigonometric functions\n"
    "  asin(x), acos(x), atan(x)  Inverse trig functions\n"
    "  exp(x)              e^x\n"
    "  ln(x)               Natural logarithm\n"
    "  log10(x)            Base-10 logarithm\n"
    "  log(x,y)            Logarithm base y of x\n"
    "  sqrt(x)             Square root\n"
    "  abs(x)              Absolute value\n"
    "\n"
    "EXAMPLES:\n"
    "  >>> 2 + 3 * 4\n"
    "  2 + 3 * 4 = 14\n"
    "  >>> x = 5\n"
    "  x = 5\n"
    "  >>> sin(3.14159/2)\n"
    "  sin(3.14159/2) = 1\n"
    "  >>> area = 3.14159 * 5^2\n"
    "  area = 78.5398\n"
    "\n"
    "COMMANDS:\n"
    "  help                Show this help message\n"
    "  vars                Display all variables\n"
    "  clear               Clear all variables\n"
    "  exit                Quit calculator\n"
    "\n"
    "PREDEFINED VARIABLES: \n"
    "  pi                   The ratio of circumference to diameter\n"
    "  e                    The base of natural logarithms\n"
    "  deg2rad              Degrees to radians conversion factor\n"
    "  rad2deg              Radians to degrees conversion factor\n"
    "NOTE: Angles for trig functions are in radians.\n"
    "      Use deg2rad to convert degrees to radians.";

int main() {
    Calculator calc;
    string input;

    cout << "Calculator (in development)" << endl;
    cout << "Type 'help' for assistance." << endl;

    calc.assign("pi", 3.141592653589793);
    calc.assign("e", 2.718281828459045);
    calc.assign("deg2rad", 3.141592653589793 / 180);
    calc.assign("rad2deg", 180 / 3.141592653589793);


    while (true) {
        cout << "> ";
        getline(cin, input);
        if (input.empty()) continue;
        if (input == "exit") break;
        if (input == "help") { cout << HELP_MESSAGE << endl; continue; }
        if (input == "vars") { calc.printVars(); continue; }
        if (input == "clear") { calc.clear(); cout << "Variables cleared." << endl; continue; }
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
                long double result = calc.evaluate(move(expression));
                calc.assign(varName, result);
                cout << varName << " = " << result << endl;
            } else {
                
                long double result = calc.evaluate(move(expression));
                cout << input << " = " << result << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}