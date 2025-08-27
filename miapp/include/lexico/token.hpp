#pragma once
#include <string>
#include <cstddef>

namespace lexico {

enum class TokenType {
    // Palabras clave (subset)
    KW_CLASS, KW_PUBLIC, KW_PRIVATE, KW_PROTECTED, KW_STATIC, KW_VOID,
    KW_INT, KW_DOUBLE, KW_FLOAT, KW_BOOLEAN, KW_CHAR, KW_STRING,
    KW_IF, KW_ELSE, KW_FOR, KW_WHILE, KW_DO, KW_SWITCH, KW_CASE,
    KW_DEFAULT, KW_BREAK, KW_CONTINUE, KW_RETURN, KW_NEW, KW_THIS,
    KW_EXTENDS, KW_IMPLEMENTS, KW_IMPORT, KW_PACKAGE, KW_TRY, KW_CATCH,
    KW_FINALLY, KW_THROW, KW_THROWS, KW_INTERFACE, KW_ENUM, KW_SUPER,

    IDENTIFIER,
    INT_LITERAL,
    DOUBLE_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,

    // Operadores / separadores
    PLUS, MINUS, STAR, SLASH, PERCENT,
    PLUS_PLUS, MINUS_MINUS,
    EQUAL, PLUS_EQUAL, MINUS_EQUAL, STAR_EQUAL, SLASH_EQUAL, PERCENT_EQUAL,
    EQEQ, NOTEQ, LT, GT, LE, GE,
    ANDAND, OROR, NOT,
    AMP, BAR, CARET, TILDE, LSHIFT, RSHIFT, URSHIFT,
    AMP_EQUAL, BAR_EQUAL, CARET_EQUAL, LSHIFT_EQUAL, RSHIFT_EQUAL, URSHIFT_EQUAL,
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
    COMMA, DOT, SEMI, COLON, QUESTION,

    COMMENT_LINE,
    COMMENT_BLOCK,
    WHITESPACE,

    DYNAMIC,         // tokens añadidos por reglas dinámicas
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

} // namespace lexico
