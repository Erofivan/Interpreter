#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>

TEST(IntegerOparationsTestSuite, BasicAddition) {
    std::string code = R"(
        x = 10 + 5
        println(x)
    )";
    std::string expected = "15\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MixedOperationsWithPriority) {
    std::string code = R"(
        x = 10 + 5 * 2
        y = (10 + 5) * 2
        println(x)
        println(y)
    )";
    std::string expected = "20\n30\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, DivisionAndModulus) {
    std::string code = R"(
        x = 15 / 4
        y = 15 % 4
        println(x)
        println(y)
    )";
    std::string expected = "3.75\n3\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, Exponentiation) {
    std::string code = R"(
        x = 2 ^ 3
        y = 10 ^ 0
        println(x)
        println(y)
    )";
    std::string expected = "8\n1\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, UnaryOperators) {
    std::string code = R"(
        x = -5
        y = +10
        z = -(-3)
        println(x)
        println(y)
        println(z)
    )";
    std::string expected = "-5\n10\n3\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, Equality) {
    std::string code = R"(
        x = 10 == 10
        y = 10 == 20
        println(x)
        println(y)
    )";
    std::string expected = "true\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, Inequality) {
    std::string code = R"(
        x = 10 != 10
        y = 10 != 20
        println(x)
        println(y)
    )";
    std::string expected = "false\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, GreaterLess) {
    std::string code = R"(
        x = 10 > 5
        y = 10 < 5
        z = 10 >= 10
        w = 10 <= 9
        println(x)
        println(y)
        println(z)
        println(w)
    )";
    std::string expected = "true\nfalse\ntrue\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ComplexExpression) {
    std::string code = R"(
        x = (2 + 3) * 4 ^ 2 - 10 % 3
        println(x)
    )";
    std::string expected = "79\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, UnderlineNotation) {
    std::string code = R"(
        x = 1_000_000 + 2_500
        println(x)
    )";
    std::string expected = "1002500\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MixedTypes) {
    std::string code = R"(
        x = 10 + 3.5
        y = 5 * 2.0
        println(x)
        println(y)
    )";
    std::string expected = "13.5\n10\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ChainedOperations) {
    std::string code = R"(
        x = 5 + 3 + 2
        y = 10 - 3 - 2
        z = 2 * 3 * 4
        println(x)
        println(y)
        println(z)
    )";
    std::string expected = "10\n5\n24\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, PowerPrecedence) {
    std::string code = R"(
        x = 2 * 3 ^ 2
        y = (2 * 3) ^ 2
        println(x)
        println(y)
    )";
    std::string expected = "18\n36\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, UnaryMinusPrecedence) {
    std::string code = R"(
        x = -2 ^ 2
        y = (-2) ^ 2
        println(x)
        println(y)
    )";
    std::string expected = "-4\n4\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MixedComparisons) {
    std::string code = R"(
        x = (10 > 5) and (3 < 4)
        y = (10 == 5) or (20 != 10)
        println(x)
        println(y)
    )";
    std::string expected = "true\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, PlusEquals) {
    std::string code = R"(
        x = 10
        x += 5
        println(x)
    )";
    std::string expected = "15\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MinusEquals) {
    std::string code = R"(
        x = 20
        x -= 7
        println(x)
    )";
    std::string expected = "13\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MultiplyEquals) {
    std::string code = R"(
        x = 5
        x *= 6
        println(x)
    )";
    std::string expected = "30\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, DivideEquals) {
    std::string code = R"(
        x = 15
        x /= 4
        println(x)
    )";
    std::string expected = "3.75\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ModEquals) {
    std::string code = R"(
        x = 17
        x %= 5
        println(x)
    )";
    std::string expected = "2\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, PowerEquals) {
    std::string code = R"(
        x = 3
        x ^= 4
        println(x)
    )";
    std::string expected = "81\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, AndOperator) {
    std::string code = R"(
        x = (5 > 3) and (4 < 6)
        y = (5 > 3) and (4 > 6)
        println(x)
        println(y)
    )";
    std::string expected = "true\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, OrOperator) {
    std::string code = R"(
        x = (5 < 3) or (4 < 6)
        y = (5 < 3) or (4 > 6)
        println(x)
        println(y)
    )";
    std::string expected = "true\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, NotOperator) {
    std::string code = R"(
        x = not (5 > 3)
        y = not (5 < 3)
        println(x)
        println(y)
    )";
    std::string expected = "false\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, StringInequality) {
    std::string code = R"(
        x = "hello" != "world"
        y = "hello" != "hello"
        println(x)
        println(y)
    )";
    std::string expected = "true\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, UnaryPlusWithVariables) {
    std::string code = R"(
        x = -5
        y = +x
        z = -(+x)
        println(y)
        println(z)
    )";
    std::string expected = "-5\n5\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, CompoundLogicalExpressions) {
    std::string code = R"(
        x = ((5 > 3) and (4 < 6)) or (10 == 11)
        y = not (5 > 3) or ((4 > 6) and (10 != 11))
        println(x)
        println(y)
    )";
    std::string expected = "true\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MixedCompoundOperations) {
    std::string code = R"(
        x = 10
        x *= 2 + 3
        y = 20
        y ^= 2
        z = 15
        z %= 4 + 1
        println(x)
        println(y)
        println(z)
    )";

    std::string expected = "50\n400\n0\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, DivisionByZero) {
    std::string code = R"(
        x = 10 / 0.0
        println(x)
    )";

    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerOparationsTestSuite, ModulusByZero) {
    std::string code = R"(
        x = 10 % 0
        println(x)
    )";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerOparationsTestSuite, ExponentialNotation) {
    std::string code = R"(
        a = 1.23e4
        b = 5.67E-3
        c = 2e+5
        d = 1_000_000e-2
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "12300\n0.00567\n200000\n10000\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, FloatingPointPrecision) {
    std::string code = R"(
        a = 0.1 + 0.2
        b = 1.0 - 0.000000000000001
        println(a == 0.3)
        println(b == 1.0)
        println(a)
        println(b)
    )";
    std::string expected = "true\nfalse\n0.3\n0.999999999999999\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, FloatComparisonWithTolerance) {
    std::string code = R"(
        a = 0.1 + 0.2
        b = 0.3
        println(abs(a - b) < 1e-15)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, LargeValueOperations) {
    std::string code = R"(
        big = 1e308
        bigger = big * 2
        println(bigger)
    )";
    std::string expected = "200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, FloatCompoundOperations) {
    std::string code = R"(
        x = 10.5
        x += 0.75
        y = 5.0
        y *= 1.5
        z = 100.0
        z /= 3.0
        w = 10.0
        w ^= 2.0
        println(x)
        println(y)
        println(z)
        println(w)
    )";
    std::string expected = "11.25\n7.5\n33.(3)\n100\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, SpecialCases) {
    std::string code = R"(
        b = 4 ^ 0.5    
        c = 8 ^ (1/3)   
        d = (-8) ^ (1/3) 
        e = 2 ^ (-2)     
        
        println(b)
        println(c)
        println(d)
        println(e)
    )";
    std::string expected = "2\n1\n1\n0.25\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, SpecialCases2) {
    std::string code = R"(
        b = 0^0

        print(b)
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerOparationsTestSuite, UnaryAndBinary) {
    std::string code = R"(
        a = -2 ^ 2
        b = (-2) ^ 2
        c = -3 * -4
        d = +5 - -5
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "-4\n4\n12\n10\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, NegativeNumbers) {
    std::string code = R"(
        a = 10 % 3
        b = -10 % 3
        c = 10 % -3
        d = -10 % -3
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "1\n-1\n1\n-1\n"; 
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, Comparisons) {
    std::string code = R"(
        nan = 0/0
        println(nan == nan)
        println(nan != nan)
        println(nan < 0)
        println(nan > 0)
        println(nan == 0)
        println(nan == 1)
    )";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_FALSE(interpret(input, output));
}

TEST(IntegerOparationsTestSuite, Operations) {
    std::string code = R"(
        inf = 1e300 * 1e300
        neg_inf = -inf
        println(inf > 1e308)
        println(neg_inf < -1e308)
        println(inf + inf)
        println(inf - inf)
        println(inf * 0)
    )";
    std::string expected = "true\ntrue\n2000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\n0\n0\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ComplexExpressions) {
    std::string code = R"(
        result = 2 + 3 * 4 ^ 2 + -5 % 3
        println(result)
    )";
    std::string expected = "48\n"; 

    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, TypeChange) {
    std::string code = R"(
        x = 10
        x /= 4
        println(x)
    )";
    std::string expected = "2.5\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MixedComparison) {
    std::string code = R"(
        println(1.0 == 1)
        println(2.5 > 2)
        println(3.0 < 4)
        println(5.5 >= 5)
        println(6.0 <= 6)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, OverflowCases) {
    std::string code = R"(
        max_int = 9007199254740991 
        overflow = max_int + 2
        println(overflow == max_int + 1) 
    )";
    std::string expected = "false\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, BasicExponential) {
    std::string code = R"(
        a = 1.23e-4
        b = 5.67E+3
        c = 2e5
        d = 3E-2
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "0.000123\n5670\n200000\n0.03\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, IntegerExponents2) {
    std::string code = R"(
        a = 1e0
        b = 2e1
        c = 3e+0
        d = 4e-0
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "1\n20\n3\n4\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ExponentLimits) {
    std::string code = R"(
        min_exp = 1e-323
        max_exp = 1e308
        overflow = 1e309
        underflow = 1e-324
        println(min_exp > 0)
        println(max_exp < 1e309)
        println(overflow)
        println(underflow)
    )";
    std::string expected = "true\ntrue\n1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\n0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, NegativeNumbers2) {
    std::string code = R"(
        a = -1.23e-4
        b = -5.67E+3
        c = -2e5
        d = -3E-2
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "-0.000123\n-5670\n-200000\n-0.03\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(ExponentialOperationsTest, ArithmeticOperations) {
    std::string code = R"(
        a = 1.5e3 + 2.5e2 
        b = 2.0e4 * 1.5e-2
        c = 5.0e3 / 2.0e2  
        d = 1.0e3 % 3.0e2  
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "1750\n300\n25\n100\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, PrecisionIssues) {
    std::string code = R"(
        a = 1.0e-16 + 1.0e-16
        b = 1.0e20 + 1.0e-20
        c = 1.0e-20 == 0.0
        println(a == 2.0e-16)
        println(b == 1.0e20)
        println(c)
    )";
    std::string expected = "true\nfalse\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ComparisonOperations2) {
    std::string code = R"(
        a = 1.5e3 > 1.5e-3
        b = 2.0e4 == 20000
        c = 3.0e-2 < 0.1
        d = 1.0e10 >= 1e10
        e = 1.0e-5 <= 0.00001
        println(a)
        println(b)
        println(c)
        println(d)
        println(e)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, VerySmallValues) {
    std::string code = R"(
        a = 1e-323  
        b = 1e-324  
        c = 1e-325  
        println(a > 0)
        println(b == 0)
        println(c == 0)
    )";
    std::string expected = "true\nfalse\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ComplexExpressions2) {
    std::string code = R"(
        result = (2.5e3 + 1.5e3) * 1e-3 - 5e-1
        println(result)
    )";
    std::string expected = "3.5\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, UnaryOperations) {
    std::string code = R"(
        a = -1.5e3
        b = +2.5e-2
        c = -(-1.5e3)
        d = -(1.5e-3)
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "-1500\n0.025\n1500\n-0.0015\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, UnderscoreNotation) {
    std::string code = R"(
        a = 1_2_3.4_5e6
        b = 1_0_0e-0_2
        c = 9.8_7_6e+0_3
        println(a)
        println(b)
        println(c)
    )";
    std::string expected = "123450000\n1\n9876\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, DivisionOperations) {
    std::string code = R"(
        a = 1.0e6 / 1.0e3  
        b = 2.5e-3 / 5.0e2 
        c = 1.0e10 / 1.0e10
        d = 1.0e-10 / 1.0e10
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "1000\n0.000005\n1\n0.00000000000000000001\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, PowerOperations) {
    std::string code = R"(
        a = (1.0e3) ^ 2    
        b = (2.0e2) ^ 0.5 
        c = (1.0e-2) ^ 3  
        d = (10.0) ^ (-3.0)
        println(a)
        println(b)
        println(c)
        println(d)
    )";
    std::string expected = "1000000\n14.1421356237\n0.000001\n0.001\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, BasicEquality) {
    std::string code = R"(
        println(1 == 1.0)
        println(1 == 1e0)
        println(1.0 == 1e0)
        println(100 == 100.0)
        println(100 == 1e2)
        println(100.0 == 1e2)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}


TEST(IntegerOparationsTestSuite, ArithmeticOperations) {
    std::string code = R"(
        a = 5 + 5.0
        b = 10 - 1e1
        c = 2 * 2.0
        d = 100 / 1e2
        e = 2 ^ 3.0
        
        println(a)
        println(b)
        println(c)
        println(d)
        println(e)
    )";
    std::string expected = "10\n0\n4\n1\n8\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, ComparisonOperations) {
    std::string code = R"(
        println(5 > 5.0)
        println(10 < 10.0)
        println(3.0 >= 3)
        println(2e1 <= 20.0)
        println(100 == 1e2)
        println(50 != 5e1)
    )";
    std::string expected = "false\nfalse\ntrue\ntrue\ntrue\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, AssignmentAndUsage) {
    std::string code = R"(
        a = 10
        b = 10.0
        c = 1e1
        
        d = a * 2.0
        e = b * 2
        f = c * 2.0
        
        println(d == e)
        println(e == f)
        println(d == 20)
        println(f == 20.0)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, CompoundAssignment) {
    std::string code = R"(
        x = 10
        x += 5.0
        y = 20.0
        y -= 1e1
        z = 2
        z *= 3.0
        w = 100.0
        w /= 1e1
        
        println(x)
        println(y)
        println(z)
        println(w)
    )";
    std::string expected = "15\n10\n6\n10\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MathFunctions) {
    std::string code = R"(
        b = sqrt(4)
        c = sqrt(4e0)
    
        println(b == c)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, MixedRepresentationExpressions) {
    std::string code = R"(
        result = (5 + 2.5) * 2e1 - 10.0 / 4
        println(result)
        println(result == 147.5)
        println(result == 147.5e-0)
        println(result == 147.5e+0)
        println(result == 147.5e0)
    )";
    std::string expected = "147.5\ntrue\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, IntegerExponents) {
    std::string code = R"(
        a = 100
        b = 1e2
        c = 100.0
        d = 1.0e2
        e = 1e+2
        
        println(a == b)
        println(b == c)
        println(c == d)
        println(d == e)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, NegativeNumbers3) {
    std::string code = R"(
        println(-5 == -5.0)
        println(-10 == -1e1)
        println(-2.5 == -25e-1)
        println(-100.0 == -1e2)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, InConditionals) {
    std::string code = R"(
        if (1.0 == 1) then
            println("equal")
        else 
            println("not equal")
        end if
                
        if (2e1 > 19.0) then
            println("greater")
        else
            println("not greater")
        end if
    )";
    std::string expected = "equal\ngreater\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, Conversion) {
    std::string code = R"(
        a = 10
        b = a + 0.0  
        c = 10.5
        d = c - 0.5 
        
        println(b == 10.0)
        println(d == 10)
        println(10 == 10.0)
        println(10.5 == 10.5e0)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, EdgeCases) {
    std::string code = R"(
        max_int = 9007199254740991
        max_float = 9007199254740991.0
        max_exp = 9.007199254740991e15
        
        min_int = -max_int
        min_float = -max_float
        min_exp = -max_exp
        
        println(max_int == max_float)
        println(max_float == max_exp)
        println(min_int == min_float)
        println(min_float == min_exp)
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, LogicalOperations) {
    std::string code = R"(
        x = 1.0 and 1
        y = 0.0 or 0
        z = not 0.0
        w = not 1e0
        
        println(x)
        println(y)
        println(z)
        println(w)
    )";
    std::string expected = "1\n0\nfalse\nfalse\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOparationsTestSuite, InCollections) {
    std::string code = R"(        
        println(1 == 1.0)
        println(1.0 == 1e0)
    )";
    std::string expected = "true\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, VeryLargeAddition) {
    std::string code = R"(
        a = 1000000000000000000000000000000
        b = 1
        c = a + b
        println(c == 1000000000000000000000000000001)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, HugeMultiplication) {
    std::string code = R"(
        a = 10000000000000000000
        b = 10000000000000000000
        c = a * b
        println(c == 100000000000000000000000000000000000000)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, LargeDivision) {
    std::string code = R"(
        a = 1000000000000000000000000
        b = 1000000000000000000
        c = a / b
        println(c == 1000000)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, FloatingPointPrecision) {
    std::string code = R"(
        a = 9007199254740993 
        b = a + 0.0
        println(a == b)  
        println(b - a)  
    )";
    std::string expected = "true\n0\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, MixedPrecisionArithmetic) {
    std::string code = R"(
        a = 10000000000000000000
        b = 0.0000000000000000001
        c = a + b
        d = a * b
        println(c == a)
        println(d == 1)
    )";
    std::string expected = "false\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, LargeExponentiation) {
    std::string code = R"(
        a = 2
        b = 100
        c = a ^ b 
        println(c == 1267650600228229401496703205376)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, FloatToIntConversion) {
    std::string code = R"(
        a = 3.14159e10
        c = 31415900000
        println(a == c)
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, ModuloWithLargeNumbers) {
    std::string code = R"(
        a = 123456789012345678901234567890
        b = 1234567890
        c = a % b
        println(c == 0)  
    )";
    std::string expected = "true\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, BoundaryValueHandling) {
    std::string code = R"(
        max_int = 9223372036854775807  
        a = max_int + 1
        b = max_int * 2
        println(a == 9223372036854775808)
        println(b == 18446744073709551614)
    )";
    std::string expected = "true\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, PrecisionLossDetection) {
    std::string code = R"(
        big_int = 9007199254740993  
        big_float = 9007199254740992.0
        sum1 = big_int + 0.0
        sum2 = big_float + 1
        println(sum1 == big_float)  
        println(sum2 == big_int)    
    )";
    std::string expected = "false\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, JustBigNumbers1) {
    std::string code = R"(
        big_int1 = 371264831628939042368412980468490712364293  
        big_int2 = 4182374891237489023147812908347127410892472190384701289
        println(big_int1 * big_int2)
    )";
    std::string expected = "1552768709804388601963929587258599033417095788040941796748765610090811224100110852442741754673677\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(IntegerOperationsTestSuite, JustBigNumbers2) {
    std::string code = R"(
        big_int1 = 371264831628939042368412980468490712364293  
        big_int2 = 4182374891237489023147812908347127410892472190384701289
        println(big_int2 / big_int1)
        println(big_int2 % big_int1)
    )";
    std::string expected = "11265206221895.984028354856725\n365335121483983956604725966217880951906054\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}