# Abstract Syntax Tree (AST) CLI Calculator

A command-line calculator built according to C++17 that parses expressions into an Abstract Syntax Tree (AST) for evaluation. This is a personal project.

## Features

*   Parses arithmetic expressions into a generic AST.
*   Evaluates the AST to get results.
*   Uses standard algorithms and data structures.

## To build:
Use cmake

```bash
# Clone the repository
git clone https://github.com/ccwmu/Calculator.git
cd Calculator

# Create build folder (if not already present)
mkdir build
cd build

# Run cmake and build
cmake ..
make

# Now, run the file
./calculator
