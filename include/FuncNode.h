/**
 * @file FuncNode.h
 * @brief Function operation nodes for the AST
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * This header defines all function-related (binary and non-binary) operation
 * nodes for the AST. It includes sine, cosine, tangent, and their inverse (arc)
 * equivalents. It also includes Exp, which raises a number to the power of e, 
 * natural logarithms, base 10 logs, and log that takes a value and a base. 
 * 
 */

#pragma once

#include "Node.h"

#include <cmath>
#include <memory>
#include <map>
#include <stdexcept>
#include <string>

/**
 * @class SinNode
 * @brief Node representing sine operation
 * 
 * Evaluates the sine of the child node
 */

class SinNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new SinNode
     * @param arg Operand node
     */
    SinNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the sine of the child node
     * @param variables Map of variable names to values
     * @return Sine of the child node's evaluated value
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::sin(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new SinNode(std::unique_ptr<Node>(child->clone()));
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
    std::unique_ptr<Node> child; ///< Operand

public:
    /**
     * @brief Construct a new CosNode
     * @param arg Operand node
     */
    CosNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the cosine of the child node
     * @param variables Map of variable names to values
     * @return Cosine of the child node's evaluated value
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::cos(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new CosNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class TanNode
 * @brief Node representing tangent operation
 *
 * Evaluates the tangent of the child node
 */

class TanNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:
    /**
     * @brief Construct a new TanNode
     * @param arg Operand node
     */
    TanNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the tangent of the child node
     * @param variables Map of variable names to values
     * @return Tangent of the child node's evaluated value
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::tan(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new TanNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class ArcSinNode
 * @brief Node representing inverse sine (arcsine) operation
 *
 * Evaluates the arcsine of the child node
 */

class ArcSinNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:
    /**
     * @brief Construct a new ArcSinNode
     * @param arg Operand node
     */
    ArcSinNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the arcsine of the child node
     * @param variables Map of variable names to values
     * @return Arcsine of the child node's evaluated value
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::asin(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new ArcSinNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class ArcCosNode
 * @brief Node representing inverse cosine (arccosine) operation
 *
 * Evaluates the arccosine of the child node
 */

class ArcCosNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new ArcCosNode
     * @param arg Operand node
     */
    ArcCosNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the arccosine of the child node
     * @param variables Map of variable names to values
     * @return Arccosine of the child node's evaluated value
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::acos(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new ArcCosNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class ArcTanNode
 * @brief Node representing inverse tangent (arctangent) operation
 *
 * Evaluates the arctangent of the child node
 */

class ArcTanNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new ArcTanNode
     * @param arg Operand node
     */
    ArcTanNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the arctangent of the child node
     * @param variables Map of variable names to values
     * @return Arctangent of the child node's evaluated value
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::atan(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new ArcTanNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class ExpNode
 * @brief Node representing exponential function (e^x)
 *
 * Evaluates e raised to the power of the child node's value
 */

class ExpNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new ExpNode
     * @param arg Operand node
     */
    ExpNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate e raised to the power of the child node's value
     * @param variables Map of variable names to values
     * @return e^(child node's evaluated value)
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        return std::exp(child->evaluate(variables));
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new ExpNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class LnNode
 * @brief Node representing natural logarithm (ln) operation
 *
 * Evaluates the natural logarithm of the child node's value
 * Throws an error if the value is non-positive
 */

class LnNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new LnNode
     * @param arg Operand node
     */
    LnNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the natural logarithm of the child node's value
     * @param variables Map of variable names to values
     * @return Natural logarithm of the child node's evaluated value
     * @throws std::runtime_error if the value is non-positive
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        long double val = child->evaluate(variables);
        if (val <= 0.0) {
            throw std::runtime_error("logarithm of non-positive value");
        }
        return std::log(val);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new LnNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class LogTenNode
 * @brief Node representing base-10 logarithm (log10) operation
 *
 * Evaluates the base-10 logarithm of the child node's value
 * Throws an error if the value is non-positive
 */

class LogTenNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new LogTenNode
     * @param arg Operand node
     */
    LogTenNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the base-10 logarithm of the child node's value
     * @param variables Map of variable names to values
     * @return Base-10 logarithm of the child node's evaluated value
     * @throws std::runtime_error if the value is non-positive
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        long double val = child->evaluate(variables);
        if (val <= 0.0) {
            throw std::runtime_error("logarithm of non-positive value");
        }
        return std::log10(val);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new LogTenNode(std::unique_ptr<Node>(child->clone()));
    }
};

/**
 * @class LogNode
 * @brief Node representing logarithm with arbitrary base operation
 *
 * Evaluates the logarithm of a value with a specified base
 * Throws an error if the base is 1 or non-positive, or if the value is non-positive
 */

class LogNode : public Node {
private:
    std::unique_ptr<Node> val; ///< Value to take the logarithm of
    std::unique_ptr<Node> base; ///< Base of the logarithm

public:

    /**
     * @brief Construct a new LogNode
     * @param value Node representing the value to take the logarithm of
     * @param base Node representing the base of the logarithm
     */
    LogNode(std::unique_ptr<Node> value, std::unique_ptr<Node> base)
        : val(std::move(value)), base(std::move(base)) {}

    /**
     * @brief Evaluate the logarithm of a value with a specified base
     * @param variables Map of variable names to values
     * @return Logarithm of the value with the specified base
     * @throws std::runtime_error if the base is 1 or non-positive, or if the value is non-positive
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        long double baseValue = base->evaluate(variables);
        if (baseValue == 1.0) {
            throw std::runtime_error("logarithm base of 1");
        }
        if (baseValue <= 0.0 || val->evaluate(variables) <= 0.0) {
            throw std::runtime_error("logarithm of non-positive value");
        }
        return std::log(val->evaluate(variables)) / log(baseValue);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new LogNode(std::unique_ptr<Node>(val->clone()), std::unique_ptr<Node>(base->clone()));
    }
};

/**
 * @class SqrtNode
 * @brief Node representing square root operation
 *
 * Evaluates the square root of the child node's value
 * Throws an error if the value is negative
 */

class SqrtNode : public Node {
private:
    std::unique_ptr<Node> child; ///< Operand

public:

    /**
     * @brief Construct a new SqrtNode
     * @param arg Operand node
     */
    SqrtNode(std::unique_ptr<Node> arg)
        : child(std::move(arg)) {}

    /**
     * @brief Evaluate the square root of the child node's value
     * @param variables Map of variable names to values
     * @return Square root of the child node's evaluated value
     * @throws std::runtime_error if the value is negative
     */
    long double evaluate(const std::map<std::string, long double>& variables) const override {
        long double val = child->evaluate(variables);
        if (val < 0.0) {
            throw std::runtime_error("square root of negative value");
        }
        return std::sqrt(val);
    }

    /**
     * @brief Creates a deep copy of the node
     * @return Pointer to the cloned node
     */
    Node* clone() const override {
        return new SqrtNode(std::unique_ptr<Node>(child->clone()));
    }
};
