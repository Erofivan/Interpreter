#ifndef _ITMOSCRIPT_LIB_AST_HPP_
#define _ITMOSCRIPT_LIB_AST_HPP_

#include <memory>
#include <string>
#include <vector>

struct ExprVisitor;
struct StmtVisitor;

struct Expr { 
    size_t line_num;
    size_t col_num;

    Expr(size_t line_num = 0, size_t col_num = 0) 
        : line_num(line_num), col_num(col_num) {}

    virtual ~Expr() = default;

    virtual std::shared_ptr<class Value> AcceptVisitor(ExprVisitor* visitor) = 0;
};

struct Stmt { 
    size_t line_num;
    size_t col_num;

    Stmt(size_t line_num = 0, size_t col_num = 0) 
        : line_num(line_num), col_num(col_num) {}

    virtual ~Stmt() = default;

    virtual void AcceptVisitor(StmtVisitor* visitor) = 0;
};

////////////////////////////////////////////////////////////////////////////////
//                          Expressions declarations                          //
////////////////////////////////////////////////////////////////////////////////

struct NumberExpr : public Expr {
    std::string value;

    NumberExpr(const std::string& value, size_t line_num, size_t col_num)
        : value(value),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct StringExpr : public Expr {
    std::string value;

    StringExpr(const std::string& value, size_t line_num, size_t col_num) 
        : value(value),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct BoolExpr : public Expr {
    bool value;

    BoolExpr(bool val, size_t line_num, size_t col_num) 
        : value(val),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct NilExpr : public Expr {
    NilExpr(size_t line_num, size_t col_num) 
        : Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct VariableExpr : public Expr {
    std::string name;

    VariableExpr(const std::string& name, size_t line_num, size_t col_num) 
        : name(name),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct BinaryExpr : public Expr {
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(const std::string& op, 
               std::unique_ptr<Expr> left, std::unique_ptr<Expr> right, 
               size_t line_num, size_t col_num)
        : op(op), 
          left(std::move(left)), right(std::move(right)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct UnaryExpr : public Expr {
    std::string op;
    std::unique_ptr<Expr> expr;

    UnaryExpr(const std::string& op, 
              std::unique_ptr<Expr> expr, 
              size_t line_num, size_t col_num)
        : op(op), 
          expr(std::move(expr)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct CallExpr : public Expr {
    std::unique_ptr<Expr> callable;
    std::vector<std::unique_ptr<Expr>> args;

    CallExpr(std::unique_ptr<Expr> callable, 
             std::vector<std::unique_ptr<Expr>> args, 
             size_t line_num, size_t col_num)
        : callable(std::move(callable)),
          args(std::move(args)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct IndexExpr : public Expr {
    std::unique_ptr<Expr> target;
    std::unique_ptr<Expr> index;

    IndexExpr(std::unique_ptr<Expr> target, 
              std::unique_ptr<Expr> index, 
              size_t line_num, size_t col_num)
        : target(std::move(target)), 
          index(std::move(index)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct SliceExpr : public Expr {
    std::unique_ptr<Expr> target;
    std::unique_ptr<Expr> start;
    std::unique_ptr<Expr> end;
    std::unique_ptr<Expr> step;
    SliceExpr(std::unique_ptr<Expr> target,
              std::unique_ptr<Expr> start,
              std::unique_ptr<Expr> end,
              std::unique_ptr<Expr> step,
              size_t line_num, size_t col_num)
        : target(std::move(target)),
          start(std::move(start)),
          end(std::move(end)),
          step(std::move(step)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct ListExpr : public Expr {
    std::vector<std::unique_ptr<Expr>> elements;

    ListExpr(std::vector<std::unique_ptr<Expr>> elements, 
             size_t line_num, size_t col_num)
        : elements(std::move(elements)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

struct FunctionExpr : public Expr {
    std::vector<std::string> params;
    std::vector<std::unique_ptr<Stmt>> body;

    FunctionExpr(std::vector<std::string> params, 
                 std::vector<std::unique_ptr<Stmt>> body, 
                 size_t line_num, size_t col_num)
        : params(std::move(params)), 
          body(std::move(body)),
          Expr(line_num, col_num) {}

    std::shared_ptr<Value> AcceptVisitor(ExprVisitor* visitor) override;
};

////////////////////////////////////////////////////////////////////////////////
//                          Statements declarations                           //
////////////////////////////////////////////////////////////////////////////////

struct ExprStmt : public Stmt {
    std::unique_ptr<Expr> expr;

    ExprStmt(std::unique_ptr<Expr> expr, 
             size_t line_num, size_t col_num) 
        : expr(std::move(expr)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct AssignStmt : public Stmt {
    std::string value;
    std::unique_ptr<Expr> expr;

    AssignStmt(std::string value, 
               std::unique_ptr<Expr> expr, 
               size_t line_num, size_t col_num)
        : value(std::move(value)), 
          expr(std::move(expr)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct IfStmt : public Stmt {
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmt>> then_branch;
    std::vector<std::pair<std::unique_ptr<Expr>, std::vector<std::unique_ptr<Stmt>>>> else_if_clauses;
    std::vector<std::unique_ptr<Stmt>> else_branch;

    IfStmt(std::unique_ptr<Expr> condition,
           std::vector<std::unique_ptr<Stmt>> then_branch,
           std::vector<std::pair<std::unique_ptr<Expr>, std::vector<std::unique_ptr<Stmt>>>> else_if_clauses,
           std::vector<std::unique_ptr<Stmt>> else_branch, 
           size_t line_num, size_t col_num)
        : condition(std::move(condition)),
          then_branch(std::move(then_branch)),
          else_if_clauses(std::move(else_if_clauses)),
          else_branch(std::move(else_branch)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct ForStmt : public Stmt {
    std::string varName;
    std::unique_ptr<Expr> iterable;
    std::vector<std::unique_ptr<Stmt>> body;

    ForStmt(std::string varName, 
            std::unique_ptr<Expr> iterable, 
            std::vector<std::unique_ptr<Stmt>> body, 
            size_t line_num, size_t col_num)
        : varName(std::move(varName)), 
          iterable(std::move(iterable)), 
          body(std::move(body)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct WhileStmt : public Stmt {
    std::unique_ptr<Expr> condition;
    std::vector<std::unique_ptr<Stmt>> body;

    WhileStmt(std::unique_ptr<Expr> condition, 
              std::vector<std::unique_ptr<Stmt>> body,
              size_t line_num, size_t col_num)
        : condition(std::move(condition)), 
          body(std::move(body)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct ReturnStmt : public Stmt {
    std::unique_ptr<Expr> value;

    ReturnStmt(std::unique_ptr<Expr> value, 
               size_t line_num, size_t col_num) 
        : value(std::move(value)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct ImportStmt : public Stmt {
    std::vector<std::string> module_names;

    ImportStmt(std::vector<std::string> mods, 
               size_t line_num, size_t col_num)
        : module_names(std::move(mods)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

struct FromImportStmt : public Stmt {
    std::string module_name;
    std::vector<std::string> imports;

    FromImportStmt(std::string module_name, 
                   std::vector<std::string> imports, 
                   size_t line_num, size_t col_num)
        : module_name(std::move(module_name)), 
          imports(std::move(imports)),
          Stmt(line_num, col_num) {}

    void AcceptVisitor(StmtVisitor* visitor) override;
};

////////////////////////////////////////////////////////////////////////////////
//                          Expressions visitor                               //
////////////////////////////////////////////////////////////////////////////////

struct ExprVisitor {
    virtual ~ExprVisitor() = default;

    virtual std::shared_ptr<Value> visit(NumberExpr*) = 0;
    virtual std::shared_ptr<Value> visit(StringExpr*) = 0;
    virtual std::shared_ptr<Value> visit(BoolExpr*) = 0;
    virtual std::shared_ptr<Value> visit(NilExpr*) = 0;
    virtual std::shared_ptr<Value> visit(VariableExpr*) = 0;
    virtual std::shared_ptr<Value> visit(BinaryExpr*) = 0;
    virtual std::shared_ptr<Value> visit(UnaryExpr*) = 0;
    virtual std::shared_ptr<Value> visit(CallExpr*) = 0;
    virtual std::shared_ptr<Value> visit(IndexExpr*) = 0;
    virtual std::shared_ptr<Value> visit(SliceExpr*) = 0;
    virtual std::shared_ptr<Value> visit(ListExpr*) = 0;
    virtual std::shared_ptr<Value> visit(FunctionExpr*) = 0;
};

////////////////////////////////////////////////////////////////////////////////
//                          Statement visitor                                 //
////////////////////////////////////////////////////////////////////////////////

struct StmtVisitor {
    virtual ~StmtVisitor() = default;
    
    virtual void visit(ExprStmt*) = 0;
    virtual void visit(AssignStmt*) = 0;
    virtual void visit(IfStmt*) = 0;
    virtual void visit(ForStmt*) = 0;
    virtual void visit(WhileStmt*) = 0;
    virtual void visit(ReturnStmt*) = 0;
    virtual void visit(ImportStmt*) = 0;
    virtual void visit(FromImportStmt*) = 0;
};

#endif 