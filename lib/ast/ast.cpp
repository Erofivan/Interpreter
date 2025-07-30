#include "ast.hpp"

////////////////////////////////////////////////////////////////////////////////
//                          Expressions definitions                           //
////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Value> NumberExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> StringExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> BoolExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> NilExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> VariableExpr::AcceptVisitor(ExprVisitor* v) {
    return v->visit(this); 
}

std::shared_ptr<Value> BinaryExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> UnaryExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> CallExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> IndexExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> SliceExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> ListExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

std::shared_ptr<Value> FunctionExpr::AcceptVisitor(ExprVisitor* v) { 
    return v->visit(this); 
}

////////////////////////////////////////////////////////////////////////////////
//                          Statement definitions                             //
////////////////////////////////////////////////////////////////////////////////

void ExprStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void AssignStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void IfStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void ForStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void WhileStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void ReturnStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void ImportStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}

void FromImportStmt::AcceptVisitor(StmtVisitor* v) { 
    v->visit(this); 
}
