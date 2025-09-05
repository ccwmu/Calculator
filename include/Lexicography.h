/**
 * @file Lexicography.h
 * @brief Tokenization for mathematical expressions
 * @author Ethan Ye
 * @date 2025-8-18
 *
 * This header defines the TokenType enum and the Token struct used for
 * tokenizing the input mathematical expressions. It also declares the
 * tokenize function that converts an input string into a vector of Tokens.
 *
 */

#ifndef LEXICOGRAPHY_H
#define LEXICOGRAPHY_H

#include <string>
#include <vector>


/**
 * @enum TokenType
 * @brief Enumeration of different token types for mathematical expressions
 *
 * This enum defines the various types of tokens that can be encountered
 * in a mathematical expression, including numbers, variables, functions,
 * operators, parentheses, and special commands.
 */
enum class TokenType {
    NUMBER,    ///< Numeric literal
    VARIABLE,  ///< Variable name
    FUNCTION,  ///< Function name (e.g., sin, ln)
    PLUS,      ///< Plus operator (+)
    MINUS,     ///< Minus operator (-)
    MULTIPLY,  ///< Multiplication operator (*)
    DIVIDE,    ///< Division operator (/)
    POWER,     ///< Exponentiation operator (^)
    LEFTPAREN, ///< Left parenthesis "("
    RIGHTPAREN,///< Right parenthesis ")"
    ASSIGN,    ///< Assignment operator (=)
    COMMA,     ///< Comma (,) for function arguments
    ABS,       ///< Absolute value operator (|)
    END,       ///< End of input
    PRESERVE,  ///< Preserve command
    REMOVE     ///< Remove command
};

/**
 * @struct Token
 * @brief Represents a token in a mathematical expression
 *
 * This struct encapsulates a token's type and its string value.
 * It is used in the tokenization process to represent individual
 * components of the input expression.
 */
struct Token {
    TokenType type;    ///< Type of the token
    std::string value; ///< String value of the token

    /**
     * @brief Construct a new Token object
     * @param type The type of the token
     * @param value The string value of the token
     */
    Token(TokenType type, const std::string& value) : type(type), value(value) {}
};

/**
 * @brief Tokenizes an input mathematical expression string
 * @param input The input expression as a string
 * @return A vector of Tokens representing the tokenized expression
 * @throws std::runtime_error if an unrecognized character is encountered
 *
 * This function processes the input string character by character,
 * identifying and creating tokens for numbers, variables, functions,
 * operators, parentheses, and special commands. It returns a vector
 * of Tokens that can be used for further parsing and evaluation.
 */
std::vector<Token> tokenize(const std::string& input);

#endif //LEXICOGRAPHY_H