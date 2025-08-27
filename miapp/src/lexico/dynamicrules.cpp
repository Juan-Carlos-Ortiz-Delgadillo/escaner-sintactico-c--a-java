#include "lexico/dynamicrules.hpp"

namespace lexico {

void DynamicRules::add(const std::string& regexStr, const std::string& name, TokenType type){
    rules_.push_back(DynRule{std::regex(regexStr), type, name});
}

bool DynamicRules::matchPrefix(const std::string& buffer, std::size_t line, std::size_t col,
                               Token& out, std::size_t& consumed) const {
    for (auto& r : rules_) {
        std::smatch m;
        if (std::regex_search(buffer.begin(), buffer.end(), m, r.pattern,
                              std::regex_constants::match_continuous)) {
            out.type   = r.type;
            out.lexeme = m.str();
            out.line   = line;
            out.column = col;
            consumed   = m.length();
            return true;
        }
    }
    return false;
}

} // namespace lexico
