#ifndef _ITMOSCRIPT_LIB_STATEMENT_EXECUTOR_HPP_
#define _ITMOSCRIPT_LIB_STATEMENT_EXECUTOR_HPP_

#include "ast/ast.hpp"
#include "expression_evaluator.hpp"

class ReturnException {
public:
    std::shared_ptr<Value> value;
    explicit ReturnException(std::shared_ptr<Value> val) : value(std::move(val)) {}
};

class StatementExecutor : public StmtVisitor {
public:
    StatementExecutor(ExpressionEvaluator& evaluator) 
        : evaluator(evaluator), col_num_(0), line_(0) {}

    void visit(ExprStmt* stmt) override;
    void visit(AssignStmt* stmt) override;
    void visit(IfStmt* stmt) override;
    void visit(ForStmt* stmt) override;
    void visit(WhileStmt* stmt) override;
    void visit(ReturnStmt* stmt) override;
    void visit(ImportStmt* stmt) override;
    void visit(FromImportStmt* stmt) override;


private:
    ExpressionEvaluator& evaluator;

    int col_num_;
    int line_;
};

#endif
