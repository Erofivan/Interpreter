#ifndef _ITMOSCRIPT_LIB_TOKEN_HPP_
#define _ITMOSCRIPT_LIB_TOKEN_HPP_

#include <string>
#include <memory>

class Token {
public:
    Token(int line_num = 0, int col_num = 0) 
        : line_num(line_num), col_num(col_num) {}

    virtual ~Token() = default;
    virtual std::string text() const = 0;

    int line_num;
    int col_num;
};

class IdentifierToken : public Token {
public:
    std::string name;

    IdentifierToken(std::string name, int line_num, int col_num) 
        : name(std::move(name)), Token(line_num, col_num) {}

    std::string text() const override { 
        return name; 
    }
};

class NumberToken : public Token {
public:
    std::string value;

    NumberToken(std::string text, int line_num, int col_num) 
        : value(std::move(text)), Token(line_num, col_num) {}

    std::string text() const override { 
        return value; 
    }
};

class StringToken : public Token {
public:
    std::string value;

    StringToken(std::string value, int line_num, int col_num) 
        : value(std::move(value)), Token(line_num, col_num) {}

    std::string text() const override { 
        return value; 
    }
};

////////////////////////////////////////////////////////////////////////////////
//                        Arithmetic operations tokens                        //
////////////////////////////////////////////////////////////////////////////////

class PlusToken : public Token { 
public: 
    PlusToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "+"; 
    } 
};

struct PlusEqualToken : public Token {
    PlusEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "+="; 
    }
};

class MinusToken : public Token { 
public: 
    MinusToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "-"; 
    } 
};

struct MinusEqualToken : public Token {
    MinusEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "-="; 
    }
};

class StarToken : public Token { 
public: 
    StarToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "*"; 
    } 
};

struct StarEqualToken : public Token {
    StarEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "*="; 
    }
};

class PercentToken : public Token { 
public: 
    PercentToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "%"; 
    } 
};

struct PercentEqualToken : public Token {
    PercentEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "%="; 
    }
};


class SlashToken : public Token { 
public: 
    SlashToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "/"; 
    } 
};

struct SlashEqualToken : public Token {
    SlashEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { return "/="; }
};

class AssignToken : public Token { 
public: 
    AssignToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "="; 
    } 
};

class PowerToken : public Token { 
public: 
    PowerToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "^"; 
    } 
};

struct PowerEqualToken : public Token {
    PowerEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}
        
    std::string text() const override { 
        return "^="; 
    }
};

////////////////////////////////////////////////////////////////////////////////
//                     Comparison operators tokens                            //
////////////////////////////////////////////////////////////////////////////////

class EqualToken : public Token { 
public: 
    EqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "=="; 
    } 
};

class NotEqualToken : public Token { 
public: 
    NotEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "!="; 
    } 
};

class LessToken : public Token { 
public: 
    LessToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "<"; 
    } 
};

class LessEqualToken : public Token { 
public: 
    LessEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "<="; 
    } 
};

class GreaterToken : public Token { 
public: 
    GreaterToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ">"; 
    } 
};

class GreaterEqualToken : public Token { 
public: 
    GreaterEqualToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ">="; 
    } 
};

////////////////////////////////////////////////////////////////////////////////
//                             Priority tokens                                //
////////////////////////////////////////////////////////////////////////////////

class LParenToken : public Token { 
public: 
    LParenToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "("; 
    } 
};

class RParenToken : public Token { 
public: 
    RParenToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ")"; 
    } 
};

class LBracketToken : public Token { 
public: 
    LBracketToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "["; 
    } 
};

class RBracketToken : public Token { 
public: 
    RBracketToken(int line_num, int col_num)   
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "]"; 
    } 
};

class LBraceToken : public Token { 
public: 
    LBraceToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "{"; 
    } 
};

class RBraceToken : public Token { 
public: 
    RBraceToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "}"; 
    } 
};

class CommaToken : public Token { 
public: 
    CommaToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ","; 
    } 
};

class DotToken : public Token { 
public: 
    DotToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "."; 
    } 
};

class ColonToken : public Token { 
public: 
    ColonToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ":"; 
    } 
};

class SemiColonToken : public Token { 
public: 
    SemiColonToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ";"; 
    } 
};

class SemiColon : public Token { 
public: 
    SemiColon(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ";"; 
    } 
};


////////////////////////////////////////////////////////////////////////////////
//                            Keywords  tokens                                //
////////////////////////////////////////////////////////////////////////////////

class ThenToken : public Token { 
public: 
    ThenToken(int line_num, int col_num) 
    : Token(line_num, col_num) {}

    std::string text() const override { 
        return "then"; 
    } 
};

class IfToken : public Token { 
public: 
    IfToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "if"; 
    } 
};

class ElseToken : public Token { 
public: 
    ElseToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "else"; 
    } 
};

class ElifToken : public Token {
public:
    ElifToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "elif"; 
    } 
};

class ForToken : public Token { 
public: 
    ForToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "for"; 
    } 
};

class InToken : public Token { 
public: 
    InToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "in"; 
    } 
};

class WhileToken : public Token { 
public: 
    WhileToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "while"; 
    } 
};

class FunctionToken : public Token { 
public: 
    FunctionToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override {
        return "function"; 
    } 
};

class ReturnToken : public Token { 
public: 
    ReturnToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "return"; 
    } 
};

class EndToken : public Token { 
public: 
    EndToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "end"; 
    } 
};

class NilToken : public Token { 
public: 
    NilToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "nil"; 
    } 
};

class TrueToken : public Token { 
public: 
    bool value = true;

    TrueToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "true"; 
    } 
};

class FalseToken : public Token { 
public: 
    bool value = false;

    FalseToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "false"; 
    } 
};

class ImportToken : public Token {
public:
    ImportToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "import";
    }
};

class FromToken : public Token {
public:
    FromToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "from"; 
    }
};

class NotToken : public Token { 
public: 
    NotToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "not"; 
    } 
};

class AndToken : public Token { 
public: 
    AndToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "and"; 
    } 
};

class OrToken : public Token { 
public: 
    OrToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return "or"; 
    } 
};

////////////////////////////////////////////////////////////////////////////////
//                             End of file token                              //
////////////////////////////////////////////////////////////////////////////////


class EndOfFileToken : public Token {
public:
    EndOfFileToken(int line_num, int col_num) 
        : Token(line_num, col_num) {}

    std::string text() const override { 
        return ""; 
    }
};

#endif
