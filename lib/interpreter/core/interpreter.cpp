#include "builtins/builtins.hpp"
#include "interpreter.hpp"
#include "lexer/lexer.hpp"
#include "builtins/std/real_number.hpp"
#include "parser/parser.hpp"
#include "interpreter/debug/exceptions.hpp"
#include "interpreter/execution/statement_executor.hpp"
#include "interpreter/execution/expression_evaluator.hpp"
#include "environment/environment.hpp"
#include "value/value.hpp"

#include <sstream>

bool interpret(std::istream& in, std::ostream& out) {
    std::vector<std::string> lines;
    try {
        std::ostringstream ss;
        ss << in.rdbuf();
        std::string src = ss.str();

        {
            std::istringstream ls(src);
            std::string line;
            while (std::getline(ls, line)) lines.push_back(line);
        }

        Lexer lexer(src);
        std::vector<std::unique_ptr<Token>> tokens;
        while (true) {
            auto tok = lexer.NextToken();
            tokens.push_back(std::move(tok));
            if (dynamic_cast<EndOfFileToken*>(tokens.back().get())) break;
        }

        Parser parser(tokens);
        auto statements = parser.Parse();

        
        auto globalEnv = std::make_shared<Environment>();
        registerBuiltins(globalEnv, out);
        ExpressionEvaluator eval(globalEnv, out);
        StatementExecutor exec(eval);
        
        for (auto& stmt : statements) {
            stmt->AcceptVisitor(&exec);
        }
        return true;
    } catch (const MyError& err) {
        int ln = err.GetLineNum();
        int col = err.GetColNum();
        if (ln >= 1 && ln <= static_cast<int>(lines.size())) {
            out << lines[ln-1] << "\n";
            out << std::string(col-1, ' ') << "^\n";
        }
        out << err.ErrorType() << " in line " << ln << ": " << err.what() << std::endl;
        return false;
    } catch (const std::exception& err) {
        out << "Error: " << err.what() << std::endl;
        return false;
    }
}
