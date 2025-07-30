#include <cctype>
#include <stdexcept>

#include "interpreter/debug/exceptions.hpp"
#include "lexer.hpp"

Lexer::Lexer(const std::string& src) 
    : src_(src), cur_pos_(0) {}

void Lexer::SkipWhitespaces() {
    while (cur_pos_ < src_.size() && std::isspace(static_cast<unsigned char>(src_[cur_pos_]))) {
        if (src_[cur_pos_] == '\n') {
            ++line_num_; 
            col_num_ = 1; 
        }
        else { 
            ++col_num_; 
        }
        ++cur_pos_;
    }
}

std::unique_ptr<Token> Lexer::NextToken() {
    SkipWhitespaces();

    while (cur_pos_ + 1 < src_.size() && src_[cur_pos_] == '/' && src_[cur_pos_ + 1] == '/') {
        cur_pos_ += 2;
        col_num_ += 2;
        // Skip until end of line
        while (cur_pos_ < src_.size() && src_[cur_pos_] != '\n') {
            ++cur_pos_;
            ++col_num_;
        }
        if (cur_pos_ < src_.size() && src_[cur_pos_] == '\n') {
            ++cur_pos_;
            ++line_num_;
            col_num_ = 1;
        }
        SkipWhitespaces();
    }

    if (cur_pos_ >= src_.size()) {
        return std::make_unique<EndOfFileToken>(line_num_, col_num_);
    }

    char curr_char = src_[cur_pos_];

    int curr_token_line = line_num_;
    int curr_token_col = col_num_;

    if (std::isalpha(static_cast<unsigned char>(curr_char)) || curr_char == '_') {
        return Identifier();
    }

    if (std::isdigit(static_cast<unsigned char>(curr_char))) {
        return Number();
    }

    if (curr_char == '\"') {
        return String();
    }

    ////////////////////////////////////////////////////////////////////////////////
    //                        Arithmetic operations tokens                        //
    ////////////////////////////////////////////////////////////////////////////////

    if (curr_char == '+') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2; col_num_ += 2;
            return std::make_unique<PlusEqualToken>(curr_token_line, curr_token_col);
        } else {
            ++cur_pos_; ++col_num_;
            return std::make_unique<PlusToken>(curr_token_line, curr_token_col);
        }
    }
    if (curr_char == '-') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2; col_num_ += 2;
            return std::make_unique<MinusEqualToken>(curr_token_line, curr_token_col);
        } else {
            ++cur_pos_; ++col_num_;
            return std::make_unique<MinusToken>(curr_token_line, curr_token_col);
        }
    }
    if (curr_char == '*') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2; col_num_ += 2;
            return std::make_unique<StarEqualToken>(curr_token_line, curr_token_col);
        } else {
            ++cur_pos_; ++col_num_;
            return std::make_unique<StarToken>(curr_token_line, curr_token_col);
        }
    }
    if (curr_char == '/') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2; col_num_ += 2;
            return std::make_unique<SlashEqualToken>(curr_token_line, curr_token_col);
        } else {
            ++cur_pos_; ++col_num_;
            return std::make_unique<SlashToken>(curr_token_line, curr_token_col);
        }
    }
    if (curr_char == '%') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2; col_num_ += 2;
            return std::make_unique<PercentEqualToken>(curr_token_line, curr_token_col);
        } else {
            ++cur_pos_; ++col_num_;
            return std::make_unique<PercentToken>(curr_token_line, curr_token_col);
        }
    }

    if (curr_char == '^') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2; col_num_ += 2;
            return std::make_unique<PowerEqualToken>(curr_token_line, curr_token_col);
        } else {
            ++cur_pos_; ++col_num_;
            return std::make_unique<PowerToken>(curr_token_line, curr_token_col);
        }
    }

    if (curr_char == '=') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2;
            col_num_ += 2;
            return std::make_unique<EqualToken>(curr_token_line, curr_token_col);
        } else {
            cur_pos_++;
            col_num_++;
            return std::make_unique<AssignToken>(curr_token_line, curr_token_col);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    //                     Comparison operators tokens                            //
    ////////////////////////////////////////////////////////////////////////////////

    if (curr_char == '!') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2;
            col_num_ += 2;
            return std::make_unique<NotEqualToken>(curr_token_line, curr_token_col);
        }
    }

    if (curr_char == '<') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2;
            col_num_ += 2;
            return std::make_unique<LessEqualToken>(curr_token_line, curr_token_col);
        } else {
            cur_pos_++;
            col_num_++;
            col_num_ += 2;
            return std::make_unique<LessToken>(curr_token_line, curr_token_col);
        }
    }

    if (curr_char == '>') {
        if (cur_pos_ + 1 < src_.size() && src_[cur_pos_+1] == '=') {
            cur_pos_ += 2;
            col_num_ += 2;
            return std::make_unique<GreaterEqualToken>(curr_token_line, curr_token_col);
        } else {
            cur_pos_++;
            col_num_++;
            return std::make_unique<GreaterToken>(curr_token_line, curr_token_col);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    //                             Priority tokens                                //
    ////////////////////////////////////////////////////////////////////////////////

    if (curr_char == '(') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<LParenToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == ')') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<RParenToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == '[') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<LBracketToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == ']') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<RBracketToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == '{') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<LBraceToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == '}') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<RBraceToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == ',') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<CommaToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == '.') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<DotToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == ':') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<ColonToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == ';') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<SemiColonToken>(curr_token_line, curr_token_col); 
    }

    if (curr_char == '^') { 
        cur_pos_++;
        col_num_++; 
        return std::make_unique<PowerToken>(curr_token_line, curr_token_col); 
    }

    throw LexerError(line_num_, col_num_, std::string("unrecognized character: ") + curr_char);
}

std::unique_ptr<Token> Lexer::Identifier() {
    size_t start_pos = cur_pos_;
    size_t curr_token_line = line_num_;
    size_t curr_token_col = col_num_;

    while (cur_pos_ < src_.size() && 
          (std::isalnum(static_cast<unsigned char>(src_[cur_pos_])) || 
                                                   src_[cur_pos_] == '_')) {
        cur_pos_++;
        col_num_++;
    }

    std::string text = src_.substr(start_pos, cur_pos_ - start_pos);

    if (text == "if") return std::make_unique<IfToken>(curr_token_line, curr_token_col);
    if (text == "then") return std::make_unique<ThenToken>(curr_token_line, curr_token_col);
    if (text == "else") return std::make_unique<ElseToken>(curr_token_line, curr_token_col);
    if (text == "elif") return std::make_unique<ElifToken>(curr_token_line, curr_token_col);
    if (text == "for") return std::make_unique<ForToken>(curr_token_line, curr_token_col);
    if (text == "in") return std::make_unique<InToken>(curr_token_line, curr_token_col);
    if (text == "while") return std::make_unique<WhileToken>(curr_token_line, curr_token_col);
    if (text == "function") return std::make_unique<FunctionToken>(curr_token_line, curr_token_col);
    if (text == "and") return std::make_unique<AndToken>(curr_token_line, curr_token_col);
    if (text == "or") return std::make_unique<OrToken>(curr_token_line, curr_token_col);
    if (text == "not") return std::make_unique<NotToken>(curr_token_line, curr_token_col);
    if (text == "return") return std::make_unique<ReturnToken>(curr_token_line, curr_token_col);
    if (text == "end") return std::make_unique<EndToken>(curr_token_line, curr_token_col);
    if (text == "nil") return std::make_unique<NilToken>(curr_token_line, curr_token_col);
    if (text == "true") return std::make_unique<TrueToken>(curr_token_line, curr_token_col);
    if (text == "false") return std::make_unique<FalseToken>(curr_token_line, curr_token_col);
    if (text == "import") return std::make_unique<ImportToken>(curr_token_line, curr_token_col);
    if (text == "from")   return std::make_unique<FromToken>(curr_token_line, curr_token_col);

    return std::make_unique<IdentifierToken>(text, curr_token_line, curr_token_col);
}

std::unique_ptr<Token> Lexer::Number() {
    size_t start = cur_pos_;
    size_t curr_token_line = line_num_;
    size_t curr_token_col = col_num_;

    bool has_dot = false;
    bool has_exp = false;
    bool prev_was_underscore = false;

    while (cur_pos_ < src_.size() &&
           (isdigit(src_[cur_pos_]) || src_[cur_pos_] == '_')) {
        if (src_[cur_pos_] == '_') {
            if (prev_was_underscore) {
                throw LexerError(line_num_, col_num_, "multiple consecutive underscores are not allowed");
            }
            prev_was_underscore = true;
        } else {
            prev_was_underscore = false;
        }
        cur_pos_++; col_num_++;
    }

    if (cur_pos_ < src_.size() && src_[cur_pos_] == '.') {
        has_dot = true;
        prev_was_underscore = false;  
        cur_pos_++; col_num_++;
        while (cur_pos_ < src_.size() &&
               (isdigit(src_[cur_pos_]) || src_[cur_pos_] == '_')) {
            if (src_[cur_pos_] == '_') {
                if (prev_was_underscore) {
                    throw LexerError(line_num_, col_num_, "multiple consecutive underscores are not allowed");
                }
                prev_was_underscore = true;
            } else {
                prev_was_underscore = false;
            }
            cur_pos_++; col_num_++;
        }
    }

    if (cur_pos_ < src_.size() &&
        (src_[cur_pos_] == 'e' || src_[cur_pos_] == 'E')) {
        has_exp = true;
        prev_was_underscore = false;
        cur_pos_++; col_num_++;
        if (cur_pos_ < src_.size() &&
            (src_[cur_pos_] == '+' || src_[cur_pos_] == '-')) {
            cur_pos_++; col_num_++;
        }
        if (cur_pos_ >= src_.size() || !isdigit(src_[cur_pos_])) {
            throw LexerError(line_num_, col_num_, "invalid exponent in numeric literal");
        }
        while (cur_pos_ < src_.size() &&
               (isdigit(src_[cur_pos_]) || src_[cur_pos_] == '_')) {
            if (src_[cur_pos_] == '_') {
                if (prev_was_underscore) {
                    throw LexerError(line_num_, col_num_, "multiple consecutive underscores are not allowed");
                }
                prev_was_underscore = true;
            } else {
                prev_was_underscore = false;
            }
            cur_pos_++; col_num_++;
        }
    }
    if (src_[src_.size()-1] == '_') {
        throw LexerError(line_num_, col_num_, " invalid decimal literal");
    }

    std::string raw = src_.substr(start, cur_pos_ - start);
    std::string cleaned;
    for (char c : raw) if (c != '_') cleaned += c;

    if (!has_dot && cleaned.size() > 1 && cleaned[0] == '0') {
        for (size_t i = 1; i < cleaned.size(); ++i) {
            if (cleaned[i] != '0') {
                throw LexerError(line_num_, curr_token_col,
                    "leading zeros in decimal integer literals are not permitted");
            }
        }
    }

    return std::make_unique<NumberToken>(cleaned, curr_token_line, curr_token_col);
}


std::unique_ptr<Token> Lexer::String() {
    size_t curr_token_line = line_num_;
    size_t curr_token_col = col_num_;

    cur_pos_++; 
    col_num_++;

    std::string result;

    while (cur_pos_ < src_.size()) {
        char c = src_[cur_pos_];
        if (c == '\\') {
            if (cur_pos_ + 1 >= src_.size()) {
                break;
            }

            char next = src_[cur_pos_+1];

            if (next == '\"') { 
                result += '\"'; 
            } else if (next == '\\') { 
                result += '\\'; 
            } else if (next == 'n') { 
                result += '\n'; 
            } else { 
                result += next; 
            }

            cur_pos_ += 2;
            col_num_ += 2;
        } else if (c == '\"') {
            cur_pos_++;
            col_num_++;
            return std::make_unique<StringToken>(result, curr_token_line, curr_token_col);
        } else {
            result += c;
            cur_pos_++;
            col_num_++;
        }
    }
    throw LexerError(line_num_, col_num_, "unterminated string literal");
}
