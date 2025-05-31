// lib/parser/parser.hpp

#ifndef _ITMOSCRIPT_LIB_PARSER_HPP_
#define _ITMOSCRIPT_LIB_PARSER_HPP_

#include <stdexcept>
#include <vector>
#include <memory>

#include "lexer/token/token.hpp"
#include "ast/ast.hpp"

class Parser {
public:
    explicit Parser(const std::vector<std::unique_ptr<Token>>& tokens);
    std::vector<std::unique_ptr<Stmt>> Parse();

private:
    size_t pos = 0;
    const std::vector<std::unique_ptr<Token>>& tokens;

    template<typename T>
    bool Match();

    template<typename T>
    void Expect(const std::string& msg);

    Token* Peek() const;
    Token* PeekNext() const;

    std::unique_ptr<Stmt> Statement();
    std::unique_ptr<Stmt> IfStatement(int line, int col);
    std::unique_ptr<Stmt> ForStatement(int line, int col);
    std::unique_ptr<Stmt> WhileStatement(int line, int col);
    std::unique_ptr<Stmt> ReturnStatement(int line, int col);
    std::unique_ptr<Stmt> AssignmentOrExpr();
    std::unique_ptr<Stmt> ImportStatement(int line, int col);
    std::unique_ptr<Stmt> ImportFromStatement(int line, int col);

    std::unique_ptr<Expr> Expression();
    std::unique_ptr<Expr> LogicalAnd();
    std::unique_ptr<Expr> LogicalOr();
    std::unique_ptr<Expr> Power();
    std::unique_ptr<Expr> Equality();
    std::unique_ptr<Expr> Comparison();
    std::unique_ptr<Expr> Term();
    std::unique_ptr<Expr> Factor();
    std::unique_ptr<Expr> Unary();
    std::unique_ptr<Expr> Primary();
};

#endif
