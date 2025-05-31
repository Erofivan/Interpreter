// bin/main.cpp

#include "lib/interpreter/core/interpreter.hpp"
#include "lib/interpreter/debug/exceptions.hpp"
#include "lib/interpreter/execution/expression_evaluator.hpp"
#include "lib/interpreter/execution/statement_executor.hpp"
#include "lib/builtins/builtins.hpp"
#include "lib/lexer/token/token.hpp"
#include "lib/lexer/lexer.hpp"
#include "lib/parser/parser.hpp"


#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char** argv) {

    if (argc == 1) {
        std::shared_ptr<Environment> globalEnv = std::make_shared<Environment>();
        registerBuiltins(globalEnv, std::cout);
        ExpressionEvaluator eval(globalEnv, std::cout);
        StatementExecutor exec(eval);

        std::cout << "itmoscript REPL. Enter commands, Ctrl-C to exit.\n";
        std::string line;
        while (true) {
            std::cout << "\r>>> ";
            if (!std::getline(std::cin, line)) break;  // Ctrl-D or EOF
            if (line.empty()) continue;
            if (line == "exit") break;
            try {
                // Lex and parse the input line
                Lexer lexer(line);
                std::vector<std::unique_ptr<Token>> tokens;
                while (true) {
                    auto tok = lexer.NextToken();
                    tokens.push_back(std::move(tok));
                    if (dynamic_cast<EndOfFileToken*>(tokens.back().get())) break;
                }
                Parser parser(tokens);
                auto statements = parser.Parse();
                // Execute statements in the existing environment
                for (auto& stmt : statements) {
                    stmt->AcceptVisitor(&exec);
                }
            } catch (const MyError& err) {
                int ln = err.GetLineNum();
                int col = err.GetColNum();
                std::vector<std::string> lines;
                std::istringstream iss(line);
                std::string l;
                while (std::getline(iss, l)) lines.push_back(l);
                if (ln >= 1 && ln <= (int)lines.size()) {
                    std::cout << lines[ln-1] << "\n";
                    if (col >= 1)
                        std::cout << std::string(col-1, ' ') << "^\n";
                    std::cout << err.ErrorType() << ": " << err.what() << "\n";
                } else {
                    std::cout << err.ErrorType() << ": " << err.what() << "\n";
                }
            }
        }
        return 0;
    } else if (argc == 2) {
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Could not open file\n";
            return EXIT_FAILURE;
        }
        if (!interpret(file, std::cout)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    } else { 
        std::cerr << "Usage: itmoscript [<file.is>]\n";
        return EXIT_FAILURE;
    }
}