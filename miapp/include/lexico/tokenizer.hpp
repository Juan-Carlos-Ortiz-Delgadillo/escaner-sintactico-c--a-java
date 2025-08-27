#pragma once
#include <istream>
#include <vector>
#include <string>
#include "lexico/token.hpp"

namespace lexico {

class Tokenizer {
public:
    Tokenizer(std::istream& in);

    Token next();  // siguiente token
    void setKeywords(const std::vector<std::string>& kws);
    void reset();  // reposiciona el stream al inicio

private:
    std::istream* in_;
    int curr_ = -1;
    std::size_t line_ = 1, col_ = 1;
    std::vector<std::string> keywords_;

    int peek();
    int get();
    void unread(int c);

    bool isDigit(int c) const;
    bool isIdStart(int c) const; // letra, '_' o '$'
    bool isIdPart (int c) const; // letra, dígito, '_' o '$'

    Token makeIdentifierOrKeyword(std::size_t startCol);
    Token makeNumber(std::size_t startCol);
    Token makeString(std::size_t startCol);
    Token makeChar(std::size_t startCol);
    Token makeOperatorOrSeparator(int c, std::size_t startCol);
};

} // namespace lexico
