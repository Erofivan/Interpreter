#ifndef _ITMOSCRIPT_LIB_EXPRESSION_EVALUATOR_HPP_
#define _ITMOSCRIPT_LIB_EXPRESSION_EVALUATOR_HPP_

#include "ast/ast.hpp"
#include "environment/environment.hpp"
#include "value/value.hpp"
#include <iostream>

bool isTruthy(const ValuePtr& val);

class ExpressionEvaluator : public ExprVisitor {
public:
    ExpressionEvaluator(std::shared_ptr<Environment> env, std::ostream& out)
        : env(std::move(env)), output(out), line_(0), col_num_(0) {}

    std::shared_ptr<Value> visit(NumberExpr* expr) override;
    std::shared_ptr<Value> visit(StringExpr* expr) override;
    std::shared_ptr<Value> visit(BoolExpr* expr) override;
    std::shared_ptr<Value> visit(NilExpr* expr) override;
    std::shared_ptr<Value> visit(VariableExpr* expr) override;
    std::shared_ptr<Value> visit(BinaryExpr* expr) override;
    std::shared_ptr<Value> visit(UnaryExpr* expr) override;
    std::shared_ptr<Value> visit(CallExpr* expr) override;
    std::shared_ptr<Value> visit(IndexExpr* expr) override;
    std::shared_ptr<Value> visit(SliceExpr* expr) override;
    std::shared_ptr<Value> visit(ListExpr* expr) override;
    std::shared_ptr<Value> visit(FunctionExpr* expr) override;

    std::shared_ptr<Environment> getEnv() const { return env; }

    std::ostream& getOutput() const { return output; }

private:
    std::shared_ptr<Environment> env;
    std::ostream& output;

    int col_num_;
    int line_;
};

#endif
