#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <memory>

class Node {
public:
    virtual ~Node() = default;
    virtual double evaluate(const std::map<std::string, double>& variables) const = 0;
    virtual Node* clone() const = 0;
};

#endif // NODE_H