#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>


TEST(IntegerExpressionsTestSuite, SingleIntegerLiterals) {
    std::string code = R"(
        2
        -0
        0
        +0
        -2
        123456789
        -123456789
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, OnlyZerosIntegerLiterals) {
    std::string code = R"(
        +0
        +00000000
        +000000000000000000000000000
        0
        000000000
        000000000000000000000000000
        -0
        -000000000
        -000000000000000000000000000
        - 0
        - 000000000
        - 000000000000000000000000000
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadPositiveIntegerStartingWithZero) {
    std::string code = R"(
        0123
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadNegativeIntegerStartingWithZero) {
    std::string code = R"(
        -0123
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, IntegerAddition) {
    std::string code = R"(
        1 + 2
        1 + 2 + 3 + 4 + 5
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, IntegerSubstraction) {
    std::string code = R"(
        1 - 2
        1 - 2 - 3 - 4 - 5
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, IntegerMultiplication) {
    std::string code = R"(
        1 * 2
        1 * 2 * 3 * 4 * 5 * 0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, IntegerDivision) {
    std::string code = R"(
        10 / 2
        0 / 2 / 5
        100 / 2 / 10
        10000 / 1 / 1 / 1 / 1 / 1000
        100 / (1000 / 200)
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadIntegerDivisionByZero1) {
    std::string code = R"(
        1 / 0
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadIntegerDivisionByZero2) {
    std::string code = R"(
        0 / 0
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadIntegerDivisionByZero3) {
    std::string code = R"(
        123123 / (0 / 1231)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, UnaryOperators) {
    std::string code = R"(
        -1
        - - 1
        2 - - - - 1
        + 1
        + 1 - 0 + 2
        +++++++1
        -------0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadUnaryMultiplication) {
    std::string code = R"(
        *1
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}


TEST(IntegerExpressionsTestSuite, BadUnaryDivision) {
    std::string code = R"(
        /1
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, MixedIntegerOperations) {
    std::string code = R"(
        -123123 * 10 + (0 / 1231) / 100 - 12 + 1 - (-2)
        -123123 * 10 + (0 / 1231) / 100 - 12 + 1 + 2
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, UnderlineSeparationNotation1) {
    std::string code = R"(
        1_000_000_000
        1 + 1_000_000_000
        2_0 * 2_0_0 / 3_0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, UnderlineSeparationNotation2) {
    std::string code = R"(
        - - -0_0_0_0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}


TEST(IntegerExpressionsTestSuite, BadUnderlineSeparationNotation1) {
    std::string code = R"(
        _1000_100_10
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, BadUnderlineSeparationNotation2) {
    std::string code = R"(
        0_0_1000_100_10
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, UnclosedLeftBracket) {
    std::string code = R"(
        (1 + 2
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerExpressionsTestSuite, UnclosedRightBracket) {
    std::string code = R"(
        1 + 2)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, ReallyLargeInteger) {
    std::string code = R"(
        111111111222222222333333333444444444555555555666666666777777777888888888999999999
        -111111111222222222333333333444444444555555555666666666777777777888888888999999999
        - 111111111222222222333333333444444444555555555666666666777777777888888888999999999
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BadReallyLargePositiveIntegerStartingWithZero) {
    std::string code = R"(
        0111111111222222222333333333444444444555555555666666666777777777888888888999999999
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BadReallyLargeNegativeIntegerStartingWithZero) {
    std::string code = R"(
        -0111111111222222222333333333444444444555555555666666666777777777888888888999999999
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BigIntegerAddition) {
    std::string code = R"(
        9223372036854775807 + 9223372036854775807
        9223372036854775807 + 9223372036854775807 + 9223372036854775807 + 9223372036854775807 + 9223372036854775807
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BigIntegerSubstraction) {
    std::string code = R"(
        9223372036854775807 - 9223372036854775807
        9223372036854775807 - 9223372036854775807 - 9223372036854775807 - 9223372036854775807 - 9223372036854775807
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BigIntegerMultiplication) {
    std::string code = R"(
        9223372036854775807 * 9223372036854775807
        9223372036854775807 * 9223372036854775807 * 9223372036854775807 * 9223372036854775807 * 9223372036854775807 * 0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BigIntegerDivision) {
    std::string code = R"(
        9223000372036854700075807 / 337203685477580721121323
        9223000372036854700075807 / 1
        9223000372036854700075807 / 2
        0 / 854775807 / 36854775807
        92000233720000036854772135807 / 2 / 854775807
        920002337200003685477523807000 / 1 / 1 / 1 / 1 / 4
        920000000000233723121232036854775807 / (92200033720368547723132158070 / 23370001231231232036854775807)
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BadBigIntegerDivisionByZero1) {
    std::string code = R"(
        11111111111111111111111111111111 / 0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BadBigIntegerDivisionByZero2) {
    std::string code = R"(
        11111111111111111111111111111111 / (0 / 12312)
    )";


    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BigIntegerUnaryOperators) {
    std::string code = R"(
        -298786752614253243657648
        - - 298786752614253243657648
        298786752614253243657648 - - - - 298786752614253243657648
        + 298786752614253243657648
        + 298786752614253243657648 - 0 + 298786752614253243657648
        +++++++298786752614253243657648
        -------298786752614253243657648
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BadUnaryMultiplication) {
    std::string code = R"(
        *298786752614253243657648
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}


TEST(BigIntegerExpressionsTestSuite, BadUnaryDivision) {
    std::string code = R"(
        /298786752614253243657648
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, MixedIntegerOperations) {
    std::string code = R"(
        -23414541144 * 12432134 + (20234 / 2342134234) / 213423 - 2341234 + 12 - (-4242342134234234234123)
        -23412323495624513441234234 * 465645876 + (0 / 8357661451) / 211013466122342340 - 127698736135 + 1 + 25435445 + 0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, UnderlineSeparationNotation1) {
    std::string code = R"(
        1_000_000_000_000_000_000_000_000_000_000_000_000_000
        1 + 1_000_000_000_000_000_000_000_000_000_000_000_000_000
        2_0 * 2_000_000_000_000_000_000_000_000_000_000_000_000_000 / 3_0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, UnderlineSeparationNotation2) {
    std::string code = R"(
        - - -0_0_0_0_0000000000000000000000000000000000000000_0
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
}


TEST(BigIntegerExpressionsTestSuite, BadUnderlineSeparationNotation1) {
    std::string code = R"(
        _1000_100_10_00000000000000000000000000000
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, BadUnderlineSeparationNotation2) {
    std::string code = R"(
        0_0_1000_100_10_000000000000000000000000000000000
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, UnclosedLeftBracket) {
    std::string code = R"(
        (11111111111111111111111111111 + 222222222222222222222222222222
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(BigIntegerExpressionsTestSuite, UnclosedRightBracket) {
    std::string code = R"(
        1111111111111111111111111111111111111111 + 2222222222222222222222222222222222222222)
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}
