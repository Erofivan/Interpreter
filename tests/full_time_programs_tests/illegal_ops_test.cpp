#include <string>
#include <vector>

#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>


std::string kUnreachable = "239";

TEST(IllegalOperationsSuite, ArgumentCountMismatch) {
    std::string code = R"(
        func = function(value) return 1 end function

        func(1, 2)

        print(239) // unreachable
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
    ASSERT_FALSE(output.str().ends_with(kUnreachable));
}


// test unknown operators