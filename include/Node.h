/**
 * @file Node.h
 * @brief Abstract base class for all AST nodes
 * @author Ethan Ye
 * @date 2025-8-18
 * 
 * @details This header defines the abstract base class Node, which is the base for all node types in the AST.
 * It declares pure virtual functions for evaluating the node, cloning it, and destructing it.
 * All node classes inherit from this class and implement these functions.
*/


#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <memory>

/**
 * @class Node
 * @brief Abstract base class for all AST
 * 
 * This class is the base class for all node types in the AST.
 * It declares pure virtual functions for evaluating the node and cloning it. 
 */ 
class Node {
public:

    /**
	 * @brief Virtual destructor
     * @details Ensures that destructors of derived classes are called correctly when a Node pointer is deleted.
     * Prevents memory leaks.
    */
    virtual ~Node() = default;

    /**
     * @brief Pure virtual function to evaluate the root expression at this node.
     * @param variables Map of variable names to their values
     * @return The evaluated result as a long double
	 * @details Must be overridden by all derived classes to provide specific logic for evaluation.
    */
    virtual long double evaluate(const std::map<std::string, long double>& variables) const = 0;

    /**
	 * @brief Pure virtual function to create deep copy of the node
	 * @return Pointer to a new cloned Node
     * @details Essential for creating copies of the nodes in expression tree without slicing.
	 * The caller is responsible for managing the memory of the cloned node.
     */ 
    virtual Node* clone() const = 0;
};

#endif // NODE_H