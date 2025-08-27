#pragma once
#include <vector>
#include <regex>
#include <string>
#include "lexico/token.hpp"

namespace lexico {

struct DynRule {
    std::regex pattern;
    TokenType  type;
    std::string name;
};

class DynamicRules {
public:
    void add(const std::string& regexStr, const std::string& name,
             TokenType type = TokenType::DYNAMIC);

    // Intenta casar al inicio de 'buffer'. Si casa, devuelve token y longitud consumida.
    bool matchPrefix(const std::string& buffer, std::size_t line, std::size_t col,
                     Token& out, std::size_t& consumed) const;

private:
    std::vector<DynRule> rules_;
};

} // namespace lexico
