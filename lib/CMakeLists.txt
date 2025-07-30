set(LIB_SOURCES
    ast/ast.cpp
    builtins/builtins.cpp
    builtins/std/real_number.cpp
    environment/environment.cpp
    interpreter/core/interpreter.cpp
    interpreter/execution/expression_evaluator.cpp
    interpreter/execution/statement_executor.cpp
    lexer/lexer.cpp
    lexer/token/token.cpp
    modules/module_loader.cpp
    parser/parser.cpp
    value/value.cpp
)

add_library(itmoscript_interpreter ${LIB_SOURCES})

set(PUBLIC_HEADERS
    ast/ast.hpp
    builtins/builtins.hpp
    builtins/std/real_number.hpp
    environment/environment.hpp
    interpreter/core/interpreter.hpp
    interpreter/execution/expression_evaluator.hpp
    interpreter/execution/statement_executor.hpp
    interpreter/debug/exceptions.hpp
    lexer/lexer.hpp
    lexer/token/token.hpp
    modules/module_loader.hpp
    parser/parser.hpp
    value/value.hpp
)