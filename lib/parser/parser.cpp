// lib/parser/parser.cpp

#include "parser.hpp"
#include "interpreter/debug/exceptions.hpp"

#include <iostream>

template<typename T>
bool Parser::Match() {
    if (pos < tokens.size() && dynamic_cast<T*>(tokens[pos].get()) != nullptr) {
        pos++;
        return true;
    }
    return false;
}

template<typename T>
void Parser::Expect(const std::string& msg) {
    if (!Match<T>()) {
        Token* tok = Peek();
        if (!tok) {
            throw ParserError(0, 0, msg);
        }
        throw ParserError(tok->line_num, tok->col_num, msg);
    }
}

Token* Parser::Peek() const {
    if (pos < tokens.size()) {
        return tokens[pos].get();
    }
    return nullptr;
}

Token* Parser::PeekNext() const {
    if (pos + 1 < tokens.size()) {
        return tokens[pos + 1].get();
    }
    return nullptr;
}

Parser::Parser(const std::vector<std::unique_ptr<Token>>& tokens)
    : tokens(tokens), pos(0) {}

std::vector<std::unique_ptr<Stmt>> Parser::Parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (pos < tokens.size() && !dynamic_cast<EndOfFileToken*>(Peek())) {
        statements.push_back(Statement());
    }
    return statements;
}

std::unique_ptr<Stmt> Parser::Statement() {
    if (Match<ImportToken>()) {
        auto importTok = dynamic_cast<ImportToken*>(tokens[pos-1].get());
        return ImportStatement(importTok->line_num, importTok->col_num);
    }
    if (Match<FromToken>()) {
        auto fromTok = dynamic_cast<FromToken*>(tokens[pos-1].get());
        return ImportFromStatement(fromTok->line_num, fromTok->col_num);
    }
    if (Match<IfToken>()) {
        auto ifTok = dynamic_cast<IfToken*>(tokens[pos-1].get());
        return IfStatement(ifTok->line_num, ifTok->col_num);
    }
    if (Match<ForToken>()) {
        auto forTok = dynamic_cast<ForToken*>(tokens[pos-1].get());
        return ForStatement(forTok->line_num, forTok->col_num);
    }
    if (Match<WhileToken>()) {
        auto whileTok = dynamic_cast<WhileToken*>(tokens[pos-1].get());
        return WhileStatement(whileTok->line_num, whileTok->col_num);
    }
    if (Match<ReturnToken>()) {
        auto returnTok = dynamic_cast<ReturnToken*>(tokens[pos-1].get());
        return ReturnStatement(returnTok->line_num, returnTok->col_num);
    }
    return AssignmentOrExpr();
}

std::unique_ptr<Stmt> Parser::IfStatement(int line, int col) {
    auto condition = Expression();
    Expect<ThenToken>("expected 'then' after condition");
    
    std::vector<std::unique_ptr<Stmt>> thenStmts;
    while (pos < tokens.size() && Peek() &&
           !dynamic_cast<ElifToken*>(Peek()) &&
           !dynamic_cast<ElseToken*>(Peek()) &&
           !dynamic_cast<EndToken*>(Peek())) {
        thenStmts.push_back(Statement());
    }
    
    std::vector<std::pair<std::unique_ptr<Expr>, std::vector<std::unique_ptr<Stmt>>>> else_if_clauses;
    std::vector<std::unique_ptr<Stmt>> else_stmts;
    
    while (Match<ElifToken>()) {
        auto elif_cond = Expression();
        Expect<ThenToken>("expected 'then' after elif condition");
        
        std::vector<std::unique_ptr<Stmt>> elif_stmts;
        while (pos < tokens.size() && Peek() &&
               !dynamic_cast<ElifToken*>(Peek()) &&
               !dynamic_cast<ElseToken*>(Peek()) &&
               !dynamic_cast<EndToken*>(Peek())) {
            elif_stmts.push_back(Statement());
        }
        else_if_clauses.emplace_back(std::move(elif_cond), std::move(elif_stmts));
    }
    
    if (Match<ElseToken>()) {
        while (pos < tokens.size() && Peek() && !dynamic_cast<EndToken*>(Peek())) {
            else_stmts.push_back(Statement());
        }
    }
    
    Expect<EndToken>("expected 'end'");
    Expect<IfToken>("expected 'if'");
    
    return std::make_unique<IfStmt>(std::move(condition), 
                                    std::move(thenStmts),
                                    std::move(else_if_clauses),
                                    std::move(else_stmts),
                                    line, col);
}

std::unique_ptr<Stmt> Parser::ForStatement(int line, int col) {
    if (!dynamic_cast<IdentifierToken*>(Peek())) {
        Token* tok = Peek();
        int err_line_num = tok ? tok->line_num : 0;
        int err_col_num  = tok ? tok->col_num  : 0;
        throw ParserError(err_line_num, err_col_num, "expected identifier in for loop");
    }
    std::string name = dynamic_cast<IdentifierToken*>(Peek())->name;
    pos++;
    Expect<InToken>("expected 'in' after identifier in for loop");
    auto iterable = Expression();
    std::vector<std::unique_ptr<Stmt>> body;
    while (pos < tokens.size() && Peek() && !dynamic_cast<EndToken*>(Peek())) {
        body.push_back(Statement());
    }
    Expect<EndToken>("expected 'end' to close for loop");
    Expect<ForToken>("expected 'for' after end");
    return std::make_unique<ForStmt>(std::move(name), std::move(iterable), std::move(body), line, col);
}

std::unique_ptr<Stmt> Parser::WhileStatement(int line, int col) {
    auto condition = Expression();
    std::vector<std::unique_ptr<Stmt>> body;
    while (pos < tokens.size() && Peek() && !dynamic_cast<EndToken*>(Peek())) {
        body.push_back(Statement());
    }
    Expect<EndToken>("expected 'end' to close while loop");
    Expect<WhileToken>("expected 'while' after end");
    return std::make_unique<WhileStmt>(std::move(condition), std::move(body), line, col);
}

std::unique_ptr<Stmt> Parser::ReturnStatement(int line, int col) {
    std::unique_ptr<Expr> value;
    if (Peek() && !dynamic_cast<EndToken*>(Peek()) &&
        !dynamic_cast<ElseToken*>(Peek()) &&
        !dynamic_cast<EndOfFileToken*>(Peek())) {
        value = Expression();
    }
    return std::make_unique<ReturnStmt>(std::move(value), line, col);
}

std::unique_ptr<Stmt> Parser::AssignmentOrExpr() {
    if (dynamic_cast<IdentifierToken*>(Peek())) {
        Token* next = PeekNext();
        if (next) {
            if (dynamic_cast<PlusEqualToken*>(next) ||
                dynamic_cast<MinusEqualToken*>(next) ||
                dynamic_cast<StarEqualToken*>(next) ||
                dynamic_cast<SlashEqualToken*>(next) ||
                dynamic_cast<PowerEqualToken*>(next) ||
                dynamic_cast<PercentEqualToken*>(next)) {
                auto id_tok = dynamic_cast<IdentifierToken*>(Peek());
                std::string name = id_tok->name;
                int line = id_tok->line_num;
                int col  = id_tok->col_num;
                pos++;
                Token* op_tok = tokens[pos].get();
                pos++;
                auto rhs = Expression();
                std::string op_symbol;
                if (dynamic_cast<PlusEqualToken*>(op_tok)) op_symbol = "+";
                else if (dynamic_cast<MinusEqualToken*>(op_tok)) op_symbol = "-";
                else if (dynamic_cast<StarEqualToken*>(op_tok)) op_symbol = "*";
                else if (dynamic_cast<SlashEqualToken*>(op_tok)) op_symbol = "/";
                else if (dynamic_cast<PercentEqualToken*>(op_tok)) op_symbol = "%";
                else if (dynamic_cast<PowerEqualToken*>(op_tok)) op_symbol = "^";
                auto left_var = std::make_unique<VariableExpr>(name, line, col);
                auto bin = std::make_unique<BinaryExpr>(op_symbol, std::move(left_var), std::move(rhs), line, col);
                return std::make_unique<AssignStmt>(name, std::move(bin), line, col);
            }
            if (dynamic_cast<AssignToken*>(next)) {
                auto id_tok = dynamic_cast<IdentifierToken*>(Peek());
                std::string name = id_tok->name;
                int line = id_tok->line_num;
                int col  = id_tok->col_num;
                pos += 2;
                auto expr = Expression();
                return std::make_unique<AssignStmt>(name, std::move(expr), line, col);
            }
        }
    }
    auto expr = Expression();
    return std::make_unique<ExprStmt>(std::move(expr),
                                      expr->line_num, expr->col_num);
}


std::unique_ptr<Expr> Parser::Expression() {
    return Equality();
}

std::unique_ptr<Expr> Parser::LogicalAnd() {
    auto expr = Term();
    while (Match<AndToken>()) {
        auto op_tok = dynamic_cast<AndToken*>(tokens[pos-1].get());
        auto right = Term();
        expr = std::make_unique<BinaryExpr>("and", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
    }
    return expr;
}

std::unique_ptr<Expr> Parser::LogicalOr() {
    auto expr = LogicalAnd();
    while (Match<OrToken>()) {
        auto op_tok = dynamic_cast<OrToken*>(tokens[pos-1].get());
        auto right = LogicalAnd();
        expr = std::make_unique<BinaryExpr>("or", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
    }
    return expr;
}

std::unique_ptr<Expr> Parser::Equality() {
    auto expr = Comparison();
    while (true) {
        if (Match<EqualToken>()) {
            auto op_tok = dynamic_cast<EqualToken*>(tokens[pos-1].get());
            auto right = Comparison();
            expr = std::make_unique<BinaryExpr>("==", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
            continue;
        }
        if (Match<NotEqualToken>()) {
            auto op_tok = dynamic_cast<NotEqualToken*>(tokens[pos-1].get());
            auto right = Comparison();
            expr = std::make_unique<BinaryExpr>("!=", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
            continue;
        }
        break;
    }
    return expr;
}

std::unique_ptr<Expr> Parser::Comparison() {
    auto expr = LogicalOr();
    while (true) {
        if (Match<LessToken>()) {
            auto op_tok = dynamic_cast<LessToken*>(tokens[pos-1].get());
            auto right = LogicalOr();
            expr = std::make_unique<BinaryExpr>("<", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
            continue;
        }
        if (Match<GreaterToken>()) {
            auto op_tok = dynamic_cast<GreaterToken*>(tokens[pos-1].get());
            auto right = LogicalOr();
            expr = std::make_unique<BinaryExpr>(">", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
            continue;
        }
        if (Match<LessEqualToken>()) {
            auto op_tok = dynamic_cast<LessEqualToken*>(tokens[pos-1].get());
            auto right = LogicalOr();
            expr = std::make_unique<BinaryExpr>("<=", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
            continue;
        }
        if (Match<GreaterEqualToken>()) {
            auto op_tok = dynamic_cast<GreaterEqualToken*>(tokens[pos-1].get());
            auto right = LogicalOr();
            expr = std::make_unique<BinaryExpr>(">=", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
            continue;
        }
        break;
    }
    return expr;
}

std::unique_ptr<Expr> Parser::Term() {
    auto expr = Factor();
    while (true) {
        if (Match<PlusToken>()) {
            auto op_tok = dynamic_cast<PlusToken*>(tokens[pos-1].get());
            auto right = Factor();
            expr = std::make_unique<BinaryExpr>("+", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
        } else if (Match<MinusToken>()) {
            auto op_tok = dynamic_cast<MinusToken*>(tokens[pos-1].get());
            auto right = Factor();
            expr = std::make_unique<BinaryExpr>("-", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
        } else {
            break;
        }
    }
    return expr;
}

std::unique_ptr<Expr> Parser::Factor() {
    auto expr = Unary();
    while (true) {
        if (Match<StarToken>()) {
            auto op_tok = dynamic_cast<StarToken*>(tokens[pos-1].get());
            auto right = Unary();
            expr = std::make_unique<BinaryExpr>("*", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
        }
        else if (Match<SlashToken>()) {
            auto op_tok = dynamic_cast<SlashToken*>(tokens[pos-1].get());
            auto right = Unary();
            expr = std::make_unique<BinaryExpr>("/", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
        }
        else if (Match<PercentToken>()) {
            auto op_tok = dynamic_cast<PercentToken*>(tokens[pos-1].get());
            auto right = Unary();
            expr = std::make_unique<BinaryExpr>("%", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
        }
        else {
            break;
        }
    }
    return expr;
}

std::unique_ptr<Expr> Parser::Power() {
    auto expr = Primary();
    if (Match<PowerToken>()) {
        auto op_tok = dynamic_cast<PowerToken*>(tokens[pos-1].get());
        auto right = Power();
        expr = std::make_unique<BinaryExpr>("^", std::move(expr), std::move(right), op_tok->line_num, op_tok->col_num);
    }
    return expr;
}

std::unique_ptr<Expr> Parser::Unary() {
    if (Match<NotToken>()) {
        auto op_tok = dynamic_cast<NotToken*>(tokens[pos-1].get());
        auto right = Unary();
        return std::make_unique<UnaryExpr>("not", std::move(right), op_tok->line_num, op_tok->col_num);
    }
    if (Match<MinusToken>()) {
        auto op_tok = dynamic_cast<MinusToken*>(tokens[pos-1].get());
        auto right = Unary();
        return std::make_unique<UnaryExpr>("-", std::move(right), op_tok->line_num, op_tok->col_num);
    }
    if (Match<PlusToken>()) {
        auto op_tok = dynamic_cast<PlusToken*>(tokens[pos-1].get());
        auto right = Unary();
        return std::make_unique<UnaryExpr>("+", std::move(right), op_tok->line_num, op_tok->col_num);
    }
    return Power();
}

std::unique_ptr<Expr> Parser::Primary() {
    bool noCall = false;

    std::unique_ptr<Expr> expr;

    if (Match<NumberToken>()) {
        auto num_tok = dynamic_cast<NumberToken*>(tokens[pos-1].get());
        expr = std::make_unique<NumberExpr>(num_tok->value, num_tok->line_num, num_tok->col_num);
    } else if (Match<StringToken>()) {
        auto str_tok = dynamic_cast<StringToken*>(tokens[pos-1].get());
        expr = std::make_unique<StringExpr>(str_tok->value, str_tok->line_num, str_tok->col_num);
    } else if (Match<TrueToken>()) {
        auto bool_tok = dynamic_cast<TrueToken*>(tokens[pos-1].get());
        expr = std::make_unique<BoolExpr>(bool_tok->value, bool_tok->line_num, bool_tok->col_num);
    } else if (Match<FalseToken>()) {
        auto bool_tok = dynamic_cast<FalseToken*>(tokens[pos-1].get());
        expr = std::make_unique<BoolExpr>(bool_tok->value, bool_tok->line_num, bool_tok->col_num);
    } else if (Match<NilToken>()) {
        auto nil_tok = dynamic_cast<NilToken*>(tokens[pos-1].get());
        expr = std::make_unique<NilExpr>(nil_tok->line_num, nil_tok->col_num);
    } else if (Match<FunctionToken>()) {
        auto funcTok = dynamic_cast<FunctionToken*>(tokens[pos-1].get());
        Expect<LParenToken>("expected '(' after 'function'");
        std::vector<std::string> params;
        if (!Match<RParenToken>()) {
            do {
                Expect<IdentifierToken>("expected parameter name");
                auto id_tok = dynamic_cast<IdentifierToken*>(tokens[pos-1].get());
                params.push_back(id_tok->name);
            } while (Match<CommaToken>());
            Expect<RParenToken>("expected ')' after parameters");
        }
        std::vector<std::unique_ptr<Stmt>> body;
        while (pos < tokens.size() && !Match<EndToken>()) {
            body.push_back(Statement());
        }
        Expect<FunctionToken>("expected 'function' after 'end'");
        expr = std::make_unique<FunctionExpr>(
            std::move(params), std::move(body),
            funcTok->line_num, funcTok->col_num
        );
    } else if (Match<IdentifierToken>()) {
        auto id_tok = dynamic_cast<IdentifierToken*>(tokens[pos - 1].get());
        expr = std::make_unique<VariableExpr>(id_tok->name, id_tok->line_num, id_tok->col_num);
    } else if (Match<LParenToken>()) {
        auto lpar_tok = dynamic_cast<LParenToken*>(tokens[pos-1].get());
        auto inside = Expression();
        Expect<RParenToken>("expected ')' after expression");
        expr = std::move(inside);
        noCall = true;  // prevent treating next `(` as call
    } else if (Match<LBracketToken>()) {
        auto lbrTok = dynamic_cast<LBracketToken*>(tokens[pos-1].get());
        std::vector<std::unique_ptr<Expr>> elements;
        if (!dynamic_cast<RBracketToken*>(Peek())) {
            do {
                elements.push_back(Expression());
            } while (Match<CommaToken>());
        }
        Expect<RBracketToken>("expected ']' after list literal");
        expr = std::make_unique<ListExpr>(std::move(elements), lbrTok->line_num, lbrTok->col_num);
    }
    else {
        Token* tok = Peek();
        int err_line = tok ? tok->line_num : 0;
        int err_col  = tok ? tok->col_num  : 0;
        throw ParserError(err_line, err_col, "Unexpected token");
    }

    while (true) {
        if (!noCall && Match<LParenToken>()) {
            auto lpar_tok = dynamic_cast<LParenToken*>(tokens[pos-1].get());
            std::vector<std::unique_ptr<Expr>> args;
            if (!dynamic_cast<RParenToken*>(Peek())) {
                do {
                    args.push_back(Expression());
                } while (Match<CommaToken>());
            }
            Expect<RParenToken>("expected ')' after arguments");
            expr = std::make_unique<CallExpr>(std::move(expr), std::move(args),
                                              lpar_tok->line_num, lpar_tok->col_num);
            continue;
        }
        else if (Match<LBracketToken>()) {
            auto lbrTok = dynamic_cast<LBracketToken*>(tokens[pos-1].get());
            std::unique_ptr<Expr> start_expr;
            std::unique_ptr<Expr> end_expr;
            std::unique_ptr<Expr> step_expr;

            bool isSlice = false;
            if (Match<ColonToken>()) {
                isSlice = true;
            } else {
                start_expr = Expression();
                if (Match<ColonToken>()) {
                    isSlice = true;
                } else {
                    Expect<RBracketToken>("expected ']' after index");
                    expr = std::make_unique<IndexExpr>(std::move(expr), std::move(start_expr),
                                                       lbrTok->line_num, lbrTok->col_num);
                    continue;
                }
            }
            if (!dynamic_cast<RBracketToken*>(Peek()) && !dynamic_cast<ColonToken*>(Peek())) {
                end_expr = Expression();
            }
            if (Match<ColonToken>()) {
                if (!dynamic_cast<RBracketToken*>(Peek())) {
                    step_expr = Expression();
                }
            }
            Expect<RBracketToken>("expected ']' after slice");
            expr = std::make_unique<SliceExpr>(std::move(expr),
                                               std::move(start_expr),
                                               std::move(end_expr),
                                               std::move(step_expr),
                                               lbrTok->line_num, lbrTok->col_num);
            continue;
        }
        else {
            break;
        }
    }

    return expr;
}

std::unique_ptr<Stmt> Parser::ImportStatement(int line, int col) {
    if (!dynamic_cast<IdentifierToken*>(Peek())) {
        Token* tok = Peek();
        int err_line_num = tok ? tok->line_num : 0;
        int err_col_num  = tok ? tok->col_num  : 0;
        throw ParserError(err_line_num, err_col_num, "expected module name after 'import'");
    }
    std::vector<std::string> names;
    do {
        auto id_tok = dynamic_cast<IdentifierToken*>(Peek());
        if (!id_tok) {
            Token* tok = Peek();
            int err_line_num = tok ? tok->line_num : 0;
            int err_col_num  = tok ? tok->col_num  : 0;
            throw ParserError(err_line_num, err_col_num, "Expected module name");
        }
        names.push_back(id_tok->name);
        pos++;
    } while (Match<CommaToken>());
    return std::make_unique<ImportStmt>(std::move(names), line, col);
}

std::unique_ptr<Stmt> Parser::ImportFromStatement(int line, int col) {
    if (!Match<IdentifierToken>()) {
        Token* tok = Peek();
        int err_line_num = tok ? tok->line_num : 0;
        int err_col_num  = tok ? tok->col_num  : 0;
        throw ParserError(err_line_num, err_col_num, "expected module name after 'from'");
    }
    std::string module = dynamic_cast<IdentifierToken*>(tokens[pos-1].get())->name;
    Expect<ImportToken>("Expected 'import' after module name");
    std::vector<std::string> names;
    if (!dynamic_cast<IdentifierToken*>(Peek())) {
        Token* tok = Peek();
        int err_line_num = tok ? tok->line_num : 0;
        int err_col_num  = tok ? tok->col_num  : 0;
        throw ParserError(err_line_num, err_col_num, "expected name after 'import'");
    }
    do {
        auto id_tok = dynamic_cast<IdentifierToken*>(Peek());
        names.push_back(id_tok->name);
        pos++;
    } while (Match<CommaToken>());
    return std::make_unique<FromImportStmt>(std::move(module), std::move(names), line, col);
}