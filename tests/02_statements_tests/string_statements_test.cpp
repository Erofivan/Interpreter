#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>


TEST(StringStatementsTestSuite, RegularStringLiterals1) {
    std::string code = R"(
        a = "aaa"
        b = "bbb"
        print(a, b)
    )";

    std::string expected = "aaabbb";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, RegularStringLiterals2) {
    std::string code = R"(
        "a\na\na\n"
        s1 = "a\na\na\n"
        s2 = "b\nb\nb\n"
        print("aaa", s1, s2)
    )";

    std::string expected = "aaaa\na\na\nb\nb\nb\n";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, StringConcatenation1) {
    std::string code = R"(
        print("aaa"+"bbb")
    )";

    std::string expected = "aaabbb";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, StringConcatenation2) {
    std::string code = R"(
        "aaa" + "bbb"
        a = "aaa" 
        b = "bbb"
        c = a + b
        print(a + b, c)
    )";

    std::string expected = "aaabbbaaabbb";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, StringMultiplication1) {
    std::string code = R"(
        print("aaa"*2)
    )";


        std::string expected = "aaaaaa";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, StringMultiplication2) {
    std::string code = R"(
        "aaa" * 5
        a = "aaa"
        x = 5
        c= a * x
        print(a * x, c) 
    )";

    std::string expected = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, StringSubstraction1) {
    std::string code = R"(
        "abcdef" - "def"
        a = "abcdef"
        b = "def"
        print("abc", a-b)
    )";

    std::string expected = "abcabc";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, StringSubstraction2) {
    std::string code = R"(
        "abcdef" - "abc"
        a = "abcdef"
        b = "abc"
        print("def", a-b)
    )";

    std::string expected = "defabcdef";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, Indexation) {
    std::string code = R"(
        s = "abcdef"
        println(s)
        println(s[0], s[1], s[2], s[3], s[4], s[5])
        println(s[-1], s[-2], s[-3], s[-4], s[-5], s[-6])
        println(s[0:5])
        println(s[1:5])
        println(s[1:])
        println(s[-1::-1])
        println(s[-1:4])
        println(s[-1:-6:-2])
        print(s[-1:-6:-10])
    )";

    std::string expected = "abcdef\nabcdef\nfedcba\nabcde\nbcde\nbcdef\n\n\nfdb\nf";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringStatementsTestSuite, BadIndexation1) {
    std::string code = R"(
        s = "abcdef"
        print(s[6])
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(StringStatementsTestSuite, BadIndexation2) {
    std::string code = R"(
        s = "abcdef"
        print(s[-7])
    )";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(StringStatementsTestSuite, ShortAssinment) {
    std::string code = R"(
        s = "aaa"
        s += "b"
        print(s)
        s -= "a"
        s -= "b"
        s -= "a"
        print(s)
        s *= 2
        print(s)
    )";

    std::string expected = "aaabaaaaaa";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}