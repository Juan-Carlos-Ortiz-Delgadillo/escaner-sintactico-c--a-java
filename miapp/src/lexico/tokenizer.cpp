#include "lexico/tokenizer.hpp"
#include <cctype>

namespace lexico {

Tokenizer::Tokenizer(std::istream& in) : in_(&in) {
    keywords_ = {
        "class","public","private","protected","static","void",
        "int","double","float","boolean","char","String",
        "if","else","for","while","do","switch","case","default",
        "break","continue","return","new","this",
        "extends","implements","import","package",
        "try","catch","finally","throw","throws","interface","enum","super"
    };
}

void Tokenizer::setKeywords(const std::vector<std::string>& kws){ keywords_=kws; }
void Tokenizer::reset(){ in_->clear(); in_->seekg(0); line_=1; col_=1; curr_=-1; }

int Tokenizer::peek(){ return in_->peek(); }
int Tokenizer::get(){
    int c = in_->get();
    if (c=='\n'){ ++line_; col_=1; }
    else if (c!='\r' && c!=EOF) { ++col_; }
    return c;
}
void Tokenizer::unread(int c){ if (c!=EOF){ in_->unget(); if (col_>1) --col_; } }

bool Tokenizer::isDigit(int c) const { return c>='0' && c<='9'; }
bool Tokenizer::isIdStart(int c) const { return std::isalpha(c) || c=='_' || c=='$'; }
bool Tokenizer::isIdPart (int c) const { return std::isalnum(c) || c=='_' || c=='$'; }

Token Tokenizer::makeIdentifierOrKeyword(std::size_t startCol){
    std::string s; int c = peek();
    while (isIdPart(c)){ s.push_back((char)get()); c = peek(); }
    Token t{TokenType::IDENTIFIER,s,line_,startCol};
    // Palabras clave
    for (auto& kw: keywords_) if (s==kw){
        if (s=="class") t.type=TokenType::KW_CLASS;
        else if (s=="public") t.type=TokenType::KW_PUBLIC;
        else if (s=="private") t.type=TokenType::KW_PRIVATE;
        else if (s=="protected") t.type=TokenType::KW_PROTECTED;
        else if (s=="static") t.type=TokenType::KW_STATIC;
        else if (s=="void") t.type=TokenType::KW_VOID;
        else if (s=="int") t.type=TokenType::KW_INT;
        else if (s=="double") t.type=TokenType::KW_DOUBLE;
        else if (s=="float") t.type=TokenType::KW_FLOAT;
        else if (s=="boolean") t.type=TokenType::KW_BOOLEAN;
        else if (s=="char") t.type=TokenType::KW_CHAR;
        else if (s=="String") t.type=TokenType::KW_STRING;
        else if (s=="if") t.type=TokenType::KW_IF;
        else if (s=="else") t.type=TokenType::KW_ELSE;
        else if (s=="for") t.type=TokenType::KW_FOR;
        else if (s=="while") t.type=TokenType::KW_WHILE;
        else if (s=="do") t.type=TokenType::KW_DO;
        else if (s=="switch") t.type=TokenType::KW_SWITCH;
        else if (s=="case") t.type=TokenType::KW_CASE;
        else if (s=="default") t.type=TokenType::KW_DEFAULT;
        else if (s=="break") t.type=TokenType::KW_BREAK;
        else if (s=="continue") t.type=TokenType::KW_CONTINUE;
        else if (s=="return") t.type=TokenType::KW_RETURN;
        else if (s=="new") t.type=TokenType::KW_NEW;
        else if (s=="this") t.type=TokenType::KW_THIS;
        else if (s=="extends") t.type=TokenType::KW_EXTENDS;
        else if (s=="implements") t.type=TokenType::KW_IMPLEMENTS;
        else if (s=="import") t.type=TokenType::KW_IMPORT;
        else if (s=="package") t.type=TokenType::KW_PACKAGE;
        else if (s=="try") t.type=TokenType::KW_TRY;
        else if (s=="catch") t.type=TokenType::KW_CATCH;
        else if (s=="finally") t.type=TokenType::KW_FINALLY;
        else if (s=="throw") t.type=TokenType::KW_THROW;
        else if (s=="throws") t.type=TokenType::KW_THROWS;
        else if (s=="interface") t.type=TokenType::KW_INTERFACE;
        else if (s=="enum") t.type=TokenType::KW_ENUM;
        else if (s=="super") t.type=TokenType::KW_SUPER;
        break;
    }
    return t;
}

Token Tokenizer::makeNumber(std::size_t startCol){
    std::string s; bool hasDot=false; int c = peek();
    while (std::isdigit(c) || c=='.'){ if (c=='.'){ if (hasDot) break; hasDot=true; }
        s.push_back((char)get()); c = peek(); }
    return Token{ hasDot?TokenType::DOUBLE_LITERAL:TokenType::INT_LITERAL, s, line_, startCol };
}

Token Tokenizer::makeString(std::size_t startCol){
    std::string s; get(); // "
    int c = peek();
    while (c!=EOF){
        if (c=='\\'){ s.push_back((char)get()); s.push_back((char)get()); c = peek(); continue; }
        if (c=='\"'){ get(); break; }
        if (c=='\n' || c=='\r') break;
        s.push_back((char)get()); c = peek();
    }
    return Token{TokenType::STRING_LITERAL, s, line_, startCol};
}

Token Tokenizer::makeChar(std::size_t startCol){
    std::string s; get(); // '
    int c = get();
    if (c=='\\'){ s.push_back('\\'); s.push_back((char)get()); }
    else if (c!=EOF){ s.push_back((char)c); }
    if (peek()=='\'') get();
    return Token{TokenType::CHAR_LITERAL, s, line_, startCol};
}

Token Tokenizer::makeOperatorOrSeparator(int c0, std::size_t startCol){
    Token t; t.line=line_; t.column=startCol; t.lexeme=std::string(1,(char)c0);
    int c1 = peek();
    auto two = [&](char a,char b){ return c0==a && c1==b; };

    // Comentarios
    if (c0=='/'){
        if (c1=='/'){ get(); std::string s; int c=peek();
            while (c!=EOF && c!='\n'){ s.push_back((char)get()); c=peek(); }
            return Token{TokenType::COMMENT_LINE,s,line_,startCol};
        } else if (c1=='*'){ get(); std::string s; int prev=0,c=get();
            while (c!=EOF){ if (prev=='*' && c=='/') break; s.push_back((char)c); prev=c; c=get(); }
            return Token{TokenType::COMMENT_BLOCK,s,line_,startCol};
        }
    }

    if (two('+','+')){ get(); return Token{TokenType::PLUS_PLUS,"++",line_,startCol}; }
    if (two('-','-')){ get(); return Token{TokenType::MINUS_MINUS,"--",line_,startCol}; }
    if (two('=','=')){ get(); return Token{TokenType::EQEQ,"==",line_,startCol}; }
    if (two('!','=')){ get(); return Token{TokenType::NOTEQ,"!=",line_,startCol}; }
    if (two('<','=')){ get(); return Token{TokenType::LE,"<=",line_,startCol}; }
    if (two('>','=')){ get(); return Token{TokenType::GE,">=",line_,startCol}; }
    if (two('&','&')){ get(); return Token{TokenType::ANDAND,"&&",line_,startCol}; }
    if (two('|','|')){ get(); return Token{TokenType::OROR,"||",line_,startCol}; }
    if (two('<','<')){
        get(); if (peek()=='='){ get(); return Token{TokenType::LSHIFT_EQUAL,"<<=",line_,startCol}; }
        return Token{TokenType::LSHIFT,"<<",line_,startCol};
    }
    if (two('>','>')){
        get(); if (peek()=='>'){ get(); if (peek()=='='){ get(); return Token{TokenType::URSHIFT_EQUAL,">>>=",line_,startCol}; }
                                 return Token{TokenType::URSHIFT,">>>",line_,startCol}; }
        if (peek()=='='){ get(); return Token{TokenType::RSHIFT_EQUAL,">>=",line_,startCol}; }
        return Token{TokenType::RSHIFT,">>",line_,startCol};
    }
    if (two('+','=')){ get(); return Token{TokenType::PLUS_EQUAL,"+=",line_,startCol}; }
    if (two('-','=')){ get(); return Token{TokenType::MINUS_EQUAL,"-=",line_,startCol}; }
    if (two('*','=')){ get(); return Token{TokenType::STAR_EQUAL,"*=",line_,startCol}; }
    if (two('/','=')){ get(); return Token{TokenType::SLASH_EQUAL,"/=",line_,startCol}; }
    if (two('%','=')){ get(); return Token{TokenType::PERCENT_EQUAL,"%=",line_,startCol}; }
    if (two('&','=')){ get(); return Token{TokenType::AMP_EQUAL,"&=",line_,startCol}; }
    if (two('|','=')){ get(); return Token{TokenType::BAR_EQUAL,"|=",line_,startCol}; }
    if (two('^','=')){ get(); return Token{TokenType::CARET_EQUAL,"^=",line_,startCol}; }

    TokenType ty = TokenType::UNKNOWN;
    switch (c0){
        case '+': ty=TokenType::PLUS; break;   case '-': ty=TokenType::MINUS; break;
        case '*': ty=TokenType::STAR; break;   case '/': ty=TokenType::SLASH; break;
        case '%': ty=TokenType::PERCENT; break;case '=': ty=TokenType::EQUAL; break;
        case '<': ty=TokenType::LT; break;     case '>': ty=TokenType::GT; break;
        case '!': ty=TokenType::NOT; break;    case '&': ty=TokenType::AMP; break;
        case '|': ty=TokenType::BAR; break;    case '^': ty=TokenType::CARET; break;
        case '~': ty=TokenType::TILDE; break;  case '(': ty=TokenType::LPAREN; break;
        case ')': ty=TokenType::RPAREN; break; case '{': ty=TokenType::LBRACE; break;
        case '}': ty=TokenType::RBRACE; break; case '[': ty=TokenType::LBRACKET; break;
        case ']': ty=TokenType::RBRACKET; break; case ',': ty=TokenType::COMMA; break;
        case '.': ty=TokenType::DOT; break;    case ';': ty=TokenType::SEMI; break;
        case ':': ty=TokenType::COLON; break;  case '?': ty=TokenType::QUESTION; break;
        default:  ty=TokenType::UNKNOWN; break;
    }
    return Token{ty, std::string(1,(char)c0), line_, startCol};
}

Token Tokenizer::next(){
    // saltar blancos
    int c = peek();
    while (c==' '||c=='\t'||c=='\r'||c=='\n'||c=='\f'||c=='\b'){ get(); c=peek(); }
    if (c==EOF) return Token{TokenType::END_OF_FILE,"",line_,col_};

    std::size_t startCol = col_;
    c = get();

    if (isIdStart(c)){ unread(c); return makeIdentifierOrKeyword(startCol); }
    if (std::isdigit(c)){ unread(c); return makeNumber(startCol); }
    if (c=='\"'){ unread(c); return makeString(startCol); }
    if (c=='\''){ unread(c); return makeChar(startCol); }

    return makeOperatorOrSeparator(c, startCol);
}

} // namespace lexico
