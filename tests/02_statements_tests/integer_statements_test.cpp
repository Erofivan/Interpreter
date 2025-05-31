#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>


TEST(IntegerStatementsTestSuite, SingleIntegerLiterals) {
    std::string code = R"(
        x = 2
        x = -0
        x = 0
        x = +0
        x = -2
        y = 123456789
        z = -123456789
        print(x)
        println()
        print(y)
        println()
        print(z)
        println()
    )";

    std::string expected = "-2\n123456789\n-123456789\n";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, OnlyZerosIntegerLiterals) {
    std::string code = R"(
        print(+0)
        print(+00000000)
        x = +000000000000000000000000000
        print(x)
        print(0)
        x = 000000000
        print(x)
        print(000000000000000000000000000)
        print(-0)
        print(-000000000)
        x = -000000000000000000000000000
        print(x)
        x = - 0
        print(x)
        print(- 000000000)
        print(- 000000000000000000000000000)
    )";

    std::string expected = "000000000000";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, BadPositiveIntegerStartingWithZero1) {
    std::string code = R"(
        x = 0123
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadPositiveIntegerStartingWithZero2) {
    std::string code = R"(
        print(0123)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadNegativeIntegerStartingWithZero1) {
    std::string code = R"(
        -0123
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadNegativeIntegerStartingWithZero2) {
    std::string code = R"(
        print(-0123)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, IntegerAddition) {
    std::string code = R"(
        x = 1 + 2
        y = x + 3 + 4 + 5
        z = (y + (3 + 4) + (5))
        print(x)
        print(y)
        print(z)
    )";

    std::string expected = "31527";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, IntegerSubstraction) {
    std::string code = R"(
        x = 1 - 2
        y = x - 3 - 4 - 5
        z = (y - (3 - 4) - (5))
        print(x)
        print(y)
        print(z)
    )";

    std::string expected = "-1-13-17";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, IntegerMultiplication) {
    std::string code = R"(
        x = 1 * 2
        y = x * 3 * 4 * 5 * 0
        z = (1 * 2 * (y * 4) * (5))
        print(x)
        print(y)
        print(z)
    )";

    std::string expected = "200";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, IntegerDivision) {
    std::string code = R"(
        x = 10 / 2
        y = 0 / 2 / x
        z = 100 / 2 / 10
        print(x)
        print(y)
        print(z)
        println(10000 / 1 / 1 / 1 / 1 / 1000)
        print(100 / (1000 / 200))
    )";

    std::string expected = "50510\n20";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, BadIntegerDivisionByZero1) {
    std::string code = R"(
        x = 1 / 0
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadIntegerDivisionByZero2) {
    std::string code = R"(
        print(1 / 0)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadIntegerDivisionByZero3) {
    std::string code = R"(
        x = 0 / 0
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadIntegerDivisionByZero4) {
    std::string code = R"(
        print(0 / 0)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadIntegerDivisionByZero5) {
    std::string code = R"(
        x = 123123 / (0 / 1231)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadIntegerDivisionByZero6) {
    std::string code = R"(
        print(123123 / (0 / 1231))
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, UnaryOperators) {
    std::string code = R"(
        x = -1
        y = - - 1
        z = 2 - - - - 1
        print(x)
        print(y)
        print(z)
        print(+ 1)
        print(+ 1 - 0 + 2)
        print(-------1)
        print(-------0)
        print(--------1)
    )";

    std::string expected = "-11313-101";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, BadUnaryMultiplication1) {
    std::string code = R"(
        x = *1
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadUnaryMultiplication2) {
    std::string code = R"(
        print(*1)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}



TEST(IntegerStatementsTestSuite, BadUnaryDivision1) {
    std::string code = R"(
        x = /1
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadUnaryDivision2) {
    std::string code = R"(
        print(/1)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, MixedIntegerOperations) {
    std::string code = R"(
        x = -123123 * 10 + (0 / 1231) / 100 - 12 + 1 - (-2)
        println(x)
        print(-123123 * 10 + (0 / 1231) / 100 - 12 + 1 + 2)
    )";

    std::string expected = "-1231239\n-1231239";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, UnderlineSeparationNotation1) {
    std::string code = R"(
        x = 1_000_000_000
        y = 1 + 1_000_000_000
        z = 2_0 * 2_0_0 / 3_0
        println(x)
        println(y)
        print(z)
    )";

    std::string expected = "1000000000\n1000000001\n133.(3)";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, UnderlineSeparationNotation2) {
    std::string code = R"(
        x = - - -0_0_0_0
        print(x)
    )";

    std::string expected = "0";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}


TEST(IntegerStatementsTestSuite, BadUnderlineSeparationNotation1) {
    std::string code = R"(
        x = _1000_100_10
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadUnderlineSeparationNotation2) {
    std::string code = R"(
        print(_1000_100_10)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadUnderlineSeparationNotation3) {
    std::string code = R"(
        x = 0_0_1000_100_10
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadUnderlineSeparationNotation4) {
    std::string code = R"(
        print(0_0_1000_100_10)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, UnclosedLeftBracket) {
    std::string code = R"(
        (1 + 2
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, UnclosedRightBracket1) {
    std::string code = R"(
        1 + 2)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, UnclosedRightBracket2) {
    std::string code = R"(
        print((1+2)*3+4))
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, VariableWIthUnderlines) {
    std::string code = R"(
        x = 10
        _x = 10
        x_ = 10
        __x = 10
        x__ = 10
        _x__ = 10
        __x_ = 10
        _x_ = 10
        __x__ = 10
        print(x, _x, x_, __x, x__, _x__, __x_, _x_, __x__)
    )";

    std::string expected = "101010101010101010";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, BadNumberWithUnderlines1) {
    std::string code = R"(
        x = 1__0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, BadNumberWithUnderlines2) {
    std::string code = R"(
        x = 1_0_
    )";

    std::istringstream input(code);
    std::ostringstream output;

    std::cout << output.str();

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerStatementsTestSuite, Register) {
    std::string code = R"(
        x = 1
        X = 2
        print(x, X)
    )";

    std::string expected = "12";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerStatementsTestSuite, BadNumberWithUnderlines3) {
    std::string code = R"(
        x = 1_0_1_0____10
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

