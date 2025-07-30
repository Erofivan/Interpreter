#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>

TEST(FunctionsTestSuite, Fibonacci) {
    std::string code = R"(
        fib = function(n)
            if n == 0 then
                return 0
            end if

            a = 0
            b = 1

            for i in range(n - 1)
                c = a + b
                a = b
                b = c
            end for

            return b
        end function


        print(fib(10))
    )";

    std::string expected = "55";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(FunctionsTestSuite, FizzBuzz) {
    std::string code = R"(
        fizzBuzz = function(n)
            for i in range(1, n)
                s = "Fizz" * (i % 3 == 0) + "Buzz" * (i % 5 == 0)
                if s == "" then
                    print(i)
                else
                    print(s)
                end if
            end for
        end function

        fizzBuzz(100)
    )";

    std::string expected = "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617Fizz19BuzzFizz2223FizzBuzz26Fizz2829FizzBuzz3132Fizz34BuzzFizz3738FizzBuzz41Fizz4344FizzBuzz4647Fizz49BuzzFizz5253FizzBuzz56Fizz5859FizzBuzz6162Fizz64BuzzFizz6768FizzBuzz71Fizz7374FizzBuzz7677Fizz79BuzzFizz8283FizzBuzz86Fizz8889FizzBuzz9192Fizz94BuzzFizz9798Fizz";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(FunctionsTestSuite, Maximum) {
    std::string code = R"(
        max = function(arr)
            if len(arr) == 0 then
                return nil
            end if

            m = arr[0]

            for i in arr
                if i > m then m = i end if
            end for

            return m
        end function

        print(max([10, -1, 0, 2, 2025, 239]))
    )";

    std::string expected = "2025";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}


TEST(FunctionsTestSuite, SimpleFunctionTest) {
    std::string code = R"(
        incr = function(value)
            return value + 1
        end function

        x = incr(2)
        print(x)
    )";

    std::string expected = "3";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}


TEST(FunctionsTestSuite, FunctionAsArgTest) {
    std::string code = R"(
        incr = function(value)
            return value + 1
        end function

        printresult = function(value, func)
            result = func(value)
            print(result)
        end function

        printresult(2, incr)
    )";

    std::string expected = "3";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}


TEST(FunctionsTestSuite, NestedFunctionTest) {
    std::string code = R"(
        incr_and_print = function(value)
            incr = function(value)
                return value + 1
            end function

            print(incr(value))
        end function

        incr_and_print(2)
    )";

    std::string expected = "3";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}


TEST(FunctionsTestSuite, FunnySyntaxTest) {
    std::string code = R"(
        funcs = [
            function() return 1 end function,
            function() return 2 end function,
            function() return 3 end function
        ]

        print(funcs[0]())
        print(funcs[1]())
        print(funcs[2]())
    )";

    std::string expected = "123";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}
