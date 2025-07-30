#ifndef _ITMOSCRIPT_LIB_LEXER_HPP_
#define _ITMOSCRIPT_LIB_LEXER_HPP_

#include <string>
#include <memory>

#include "lexer/token/token.hpp"

class Lexer {
public:
    Lexer(const std::string& src);
    
    std::unique_ptr<Token> NextToken();

private:
    const std::string& src_;
    size_t cur_pos_ = 0;

    void SkipWhitespaces();
    
    std::unique_ptr<Token> Identifier();
    std::unique_ptr<Token> Number();
    std::unique_ptr<Token> String();

    size_t line_num_ = 1;
    size_t col_num_ = 1;
};

#endif
