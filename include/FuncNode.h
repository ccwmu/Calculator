/**
 * @file FuncNode.h
 * @brief Function operation nodes for the AST
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * This header defines all function-realted (binary and non-binary) operation
 * nodes for the AST. It incldes sine, cosine, tangenr, and their inverse (arc)
 * equivalents. It also includes Exp, which raises a number to the power of e, 
 * natural logarithms, base 10 logs, and log that takes a value and a base. 
 * 
 */

#ifndef FUNCNODE_H
#define FUNCNODE_H

#include "Node.h"
#include <cmath>
#include <stdexcept>

using namespace std;

/**
 * @class SinNode
 * @brief Node representing sine operation
 * 
 * Evaluates the sine of the child node
 */

class SinNode : public Node {
private:
    unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new SinNode
     * @param arg Operand node
     */
    SinNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    /**
     * @brief Evaluate the sine of the child node
     * @param variables Map of variable names to values
     * @return Sine of the child node's evaluated value
     */
    long double evaluate(const map<string, long double>& variables) const override {
        return sin(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new SinNode(unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class CosNode
 * @brief Node representing cosine operation
 * 
 * Evaluates the cosine of the child node
 */

class CosNode : public Node {
private:
    unique_ptr<Node> child;

public:
    CosNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return cos(child->evaluate(variables));
    }
    Node* clone() const override {
        return new CosNode(unique_ptr<Node>(child->clone()));
    }
};

class TanNode : public Node {
private:
    unique_ptr<Node> child;

public:
    TanNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return tan(child->evaluate(variables));
    }
    Node* clone() const override {
        return new TanNode(unique_ptr<Node>(child->clone()));
    }
};

class ArcSinNode : public Node {
private:
    unique_ptr<Node> child;

public:
    ArcSinNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return asin(child->evaluate(variables));
    }
    Node* clone() const override {
        return new ArcSinNode(unique_ptr<Node>(child->clone()));
    }
};

class ArcCosNode : public Node {
private:
    unique_ptr<Node> child;

public:
    ArcCosNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return acos(child->evaluate(variables));
    }
    Node* clone() const override {
        return new ArcCosNode(unique_ptr<Node>(child->clone()));
    }
};

class ArcTanNode : public Node {
private:
    unique_ptr<Node> child;

public:
    ArcTanNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return atan(child->evaluate(variables));
    }
    Node* clone() const override {
        return new ArcTanNode(unique_ptr<Node>(child->clone()));
    }
};

class ExpNode : public Node {
private:
    unique_ptr<Node> child;

public:
    ExpNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        return exp(child->evaluate(variables));
    }
    Node* clone() const override {
        return new ExpNode(unique_ptr<Node>(child->clone()));
    }
};

class LnNode : public Node {
private:
    unique_ptr<Node> child;

public:
    LnNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        long double val = child->evaluate(variables);
        if (val <= 0.0) {
            throw runtime_error("logarithm of non-positive value");
        }
        return log(val);
    }
    Node* clone() const override {
        return new LnNode(unique_ptr<Node>(child->clone()));
    }
};

class LogTenNode : public Node {
private:
    unique_ptr<Node> child;

public:
    LogTenNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        long double val = child->evaluate(variables);
        if (val <= 0.0) {
            throw runtime_error("logarithm of non-positive value");
        }
        return log10(val);
    }
    Node* clone() const override {
        return new LogTenNode(unique_ptr<Node>(child->clone()));
    }
};

class LogNode : public Node {
private:
    unique_ptr<Node> val;
    unique_ptr<Node> base;

public:
    LogNode(unique_ptr<Node> value, unique_ptr<Node> base)
        : val(move(value)), base(move(base)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        long double baseValue = base->evaluate(variables);
        if (baseValue == 1.0) {
            throw runtime_error("logarithm base of 1");
        }
        if (baseValue <= 0.0 || val->evaluate(variables) <= 0.0) {
            throw runtime_error("logarithm of non-positive value");
        }
        return log(val->evaluate(variables)) / log(baseValue);
    }

    Node* clone() const override {
        return new LogNode(unique_ptr<Node>(val->clone()), unique_ptr<Node>(base->clone()));
    }
};


class SqrtNode : public Node {
private:
    unique_ptr<Node> child;

public:
    SqrtNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    long double evaluate(const map<string, long double>& variables) const override {
        long double val = child->evaluate(variables);
        if (val < 0.0) {
            throw runtime_error("square root of negative value");
        }
        return sqrt(val);
    }

    Node* clone() const override {
        return new SqrtNode(unique_ptr<Node>(child->clone()));
    }
};

#endif // FUNCNODE_H