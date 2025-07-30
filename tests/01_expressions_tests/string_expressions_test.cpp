#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>


TEST(StringExpressionTestSuite, RegularStringLiterals1) {
    std::string code = R"(
        a = "aaa"
        b = "bbb"
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(StringExpressionTestSuite, RegularStringLiterals2) {
    std::string code = R"(
        "a\na\na\n"
        "b\nb\nb\n"
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(StringExpressionTestSuite, StringConcatenation) {
    std::string code = R"(
        "aaa" + "bbb"
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(StringExpressionTestSuite, StringMultiplication) {
    std::string code = R"(
        "aaa" * 5
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(StringExpressionTestSuite, StringSubstraction1) {
    std::string code = R"(
        "abcdef" -"def"
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(StringExpressionTestSuite, StringSubstraction2) {
    std::string code = R"(
        "abcdef" - "abc"
        "abcdef" - "def"
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(StringExpressionTestSuite, BadIndexation1) {
    std::string code = R"(
        "abcdef"[6]
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(StringExpressionTestSuite, BadIndexation2) {
    std::string code = R"(
        "abcdef"[-7]
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(StringExpressionTestSuite, ShortAssinment) {
    std::string code = R"(
        "aaa" += "b"
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}