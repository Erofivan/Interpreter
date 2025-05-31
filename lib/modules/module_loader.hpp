#ifndef _ITMOSCRIPT_MODULE_LOADER_HPP_
#define _ITMOSCRIPT_MODULE_LOADER_HPP_

#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>

#include "environment/environment.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "interpreter/execution/expression_evaluator.hpp"
#include "interpreter/execution/statement_executor.hpp"

class ModuleLoader {
public:
    explicit ModuleLoader(std::ostream& out) : out_(out) {}

    std::shared_ptr<Environment> LoadModule(const std::string& name) {
        if (modules_.count(name)) {
            return modules_[name];
        }

        std::string filename = name + ".is";
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot open module file: " + filename);
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

        auto moduleEnv = std::make_shared<Environment>();
        ExpressionEvaluator moduleEval(moduleEnv, out_);
        StatementExecutor moduleExec(moduleEval);

        for (auto& stmt : stmts) {
            stmt->AcceptVisitor(&moduleExec);
        }

        modules_[name] = moduleEnv;
        return moduleEnv;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Environment>> modules_;
    std::ostream& out_;
};

#endif
