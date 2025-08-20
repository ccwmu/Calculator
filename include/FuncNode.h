#ifndef FUNCNODE_H
#define FUNCNODE_H

#include "Node.h"
#include <cmath>
#include <stdexcept>
using namespace std;

class SinNode : public Node {
private:
    unique_ptr<Node> child;

public:
    SinNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    double evaluate(const map<string, double>& variables) const override {
        return sin(child->evaluate(variables));
    }
    Node* clone() const override {
        return new SinNode(unique_ptr<Node>(child->clone()));
    }
};

class CosNode : public Node {
private:
    unique_ptr<Node> child;

public:
    CosNode(unique_ptr<Node> arg)
        : child(move(arg)) {}

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
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

    double evaluate(const map<string, double>& variables) const override {
        double val = child->evaluate(variables);
        if (val <= 0.0) {
            throw runtime_error("Logarithm of non-positive value");
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

    double evaluate(const map<string, double>& variables) const override {
        double val = child->evaluate(variables);
        if (val <= 0.0) {
            throw runtime_error("Logarithm of non-positive value");
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

    double evaluate(const map<string, double>& variables) const override {
        double baseValue = base->evaluate(variables);
        if (baseValue == 1.0) {
            throw runtime_error("Logarithm base cannot be 1");
        }
        if (baseValue <= 0.0 || val->evaluate(variables) <= 0.0) {
            throw runtime_error("Logarithm of non-positive value");
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

    double evaluate(const map<string, double>& variables) const override {
        double val = child->evaluate(variables);
        if (val < 0.0) {
            throw runtime_error("Square root of negative value");
        }
        return sqrt(val);
    }

    Node* clone() const override {
        return new SqrtNode(unique_ptr<Node>(child->clone()));
    }
};

#endif // FUNCNODE_H