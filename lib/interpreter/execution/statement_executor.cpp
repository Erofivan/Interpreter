#include "statement_executor.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>

#include "interpreter/debug/exceptions.hpp"
#include "lexer/token/token.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "value/value.hpp"
#include "builtins/std/real_number.hpp"
#include "modules/module_loader.hpp" 

void StatementExecutor::visit(ExprStmt* stmt) {
    
    auto val = stmt->expr->AcceptVisitor(&evaluator);
}

void StatementExecutor::visit(AssignStmt* stmt) {
    auto val = stmt->expr->AcceptVisitor(&evaluator);
    evaluator.getEnv()->SetVariableValue(stmt->value, val);
}

void StatementExecutor::visit(IfStmt* stmt) {
    auto cond_val = stmt->condition->AcceptVisitor(&evaluator);
    auto cond_bool = std::dynamic_pointer_cast<BoolValue>(cond_val);
    if (!cond_bool) throw InterpreterError(stmt->line_num, stmt->col_num, "condition is not a boolean");
    if (cond_bool->value) {
        for (auto& s : stmt->then_branch) s->AcceptVisitor(this);
        return;
    }
    for (auto& elif : stmt->else_if_clauses) {
        auto cond2val = elif.first->AcceptVisitor(&evaluator);
        auto cond2bool = std::dynamic_pointer_cast<BoolValue>(cond2val);
        if (!cond2bool) throw InterpreterError(stmt->line_num, stmt->col_num, "condition is not a boolean");
        if (cond2bool->value) {
            for (auto& s : elif.second) s->AcceptVisitor(this);
            return;
        }
    }
    for (auto& s : stmt->else_branch) s->AcceptVisitor(this);
}

void StatementExecutor::visit(ForStmt* stmt) {
    auto iterable_val = stmt->iterable->AcceptVisitor(&evaluator);
    auto list_val = std::dynamic_pointer_cast<ListValue>(iterable_val);
    if (!list_val) {
        throw InterpreterError(stmt->line_num, stmt->col_num, "iterating over non-list");
    }
    for (auto& elem : list_val->elements) {
        evaluator.getEnv()->SetVariableValue(stmt->varName, elem);
        for (auto& s : stmt->body) {
            s->AcceptVisitor(this);
        }
    }
}

void StatementExecutor::visit(WhileStmt* stmt) {
    while (true) {
        auto cond_val = stmt->condition->AcceptVisitor(&evaluator);
        auto cond_bool = std::dynamic_pointer_cast<BoolValue>(cond_val);
        if (!cond_bool) throw InterpreterError(stmt->line_num, stmt->col_num, "condition is not a boolean");
        if (!cond_bool->value) break;
        for (auto& s : stmt->body) {
            s->AcceptVisitor(this);
        }
    }
}

void StatementExecutor::visit(ReturnStmt* stmt) {
    std::shared_ptr<Value> val = std::make_shared<NullValue>();
    if (stmt->value) {
        val = stmt->value->AcceptVisitor(&evaluator);
    }
    throw ReturnException(val);
}

void StatementExecutor::visit(ImportStmt* stmt) {
    auto current_env = evaluator.getEnv();
    for (const auto& mod : stmt->module_names) {
        std::ifstream file(mod + ".is");
        if (!file) {
            throw InterpreterError(stmt->line_num, stmt->col_num+7, "Cannot open module file: " + mod);
        }
        std::ostringstream ss; ss << file.rdbuf();
        std::string src = ss.str();
        Lexer lexer(src);
        std::vector<std::unique_ptr<Token>> tokens;
        while (true) {
            auto tok = lexer.NextToken();
            tokens.push_back(std::move(tok));
            if (dynamic_cast<EndOfFileToken*>(tokens.back().get())) break;
        }
        Parser parser(tokens);
        auto stmts = parser.Parse();

        // Execute module code in a new environment with builtins inherited
        std::shared_ptr<Environment> module_env = std::make_shared<Environment>(current_env);
        ExpressionEvaluator moduleEval(module_env, evaluator.getOutput());
        StatementExecutor moduleExec(moduleEval);

        for (auto& st : stmts) {
            if (dynamic_cast<AssignStmt*>(st.get())) {
                st->AcceptVisitor(&moduleExec);
            }
        }

        // Copy all declarations from module to current environment
        for (const auto& name : module_env->GetKeyValuesList()) {
            current_env->SetVariableValue(name, module_env->GetVariableValue(name));
        }
    }
}

void StatementExecutor::visit(FromImportStmt* stmt) {
    auto current_env = evaluator.getEnv();
    std::ifstream file(stmt->module_name + ".is");

    if (!file) {
        throw InterpreterError(stmt->line_num, stmt->col_num, "Cannot open module file: " + stmt->module_name);
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string src = ss.str();

    Lexer lexer(src);
    std::vector<std::unique_ptr<Token>> tokens;
    while (true) {
        auto tok = lexer.NextToken();
        tokens.push_back(std::move(tok));
        if (dynamic_cast<EndOfFileToken*>(tokens.back().get())) break;
    }

    Parser parser(tokens);
    auto stmts = parser.Parse();

    std::shared_ptr<Environment> module_env = std::make_shared<Environment>(nullptr);
    ExpressionEvaluator moduleEval(module_env, evaluator.getOutput());
    StatementExecutor moduleExec(moduleEval);

    bool import_all = false;
    for (const auto& name : stmt->imports) {
        if (name == "*") { import_all = true; break; }
    }
    if (import_all) {
        for (auto& st : stmts) {
            if (dynamic_cast<AssignStmt*>(st.get())) {
                st->AcceptVisitor(&moduleExec);
            }
        }
        for (const auto& key : module_env->GetKeyValuesList()) {
            current_env->SetVariableValue(key, module_env->GetVariableValue(key));
        }
    } else {
        for (const auto& name : stmt->imports) {
             for (auto& st : stmts) {
                if (auto as = dynamic_cast<AssignStmt*>(st.get())) {
                    if (as->value == name) { 
                        st->AcceptVisitor(&moduleExec);
                        break;
                    }
                }
            }
            // If not found, will throw on GetVariableValue below
        }
        for (const auto& name : stmt->imports) {
            if (name == "*") continue;
            try {
                auto value = module_env->GetVariableValue(name);
                current_env->SetVariableValue(name, value);
            } catch (const std::runtime_error&) {
                throw InterpreterError(stmt->line_num, stmt->col_num, "Name '" + name + "' not found in module");
            }
        }
    }
}