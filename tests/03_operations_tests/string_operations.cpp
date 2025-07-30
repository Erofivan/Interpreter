#include <lib/interpreter/core/interpreter.hpp>
#include <gtest/gtest.h>

TEST(StringOperationsTestSuite, BasicStringLiterals) {
    std::string code = R"(
        s1 = "Hello"
        s2 = "World"
        println(s1)
        println(s2)
    )";
    std::string expected = "Hello\nWorld\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, EscapeSequences) {
    std::string code = R"(
        s = "Line1\\nLine2\\tTab\\\"Quote\\'"
        println(s)
    )";
    std::string expected = "Line1\\nLine2\\tTab\\\"Quote\\'\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, StringComparison) {
    std::string code = R"(
        println("apple" == "apple")
        println("apple" != "orange")
        println("apple" < "banana")
        println("apple" > "Orange")
        println("apple" <= "apple")
        println("apple" >= "app")
    )";
    std::string expected = "true\ntrue\ntrue\ntrue\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, Concatenation) {
    std::string code = R"(
        s = "Hello" + " " + "World"
        println(s)
    )";
    std::string expected = "Hello World\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, SuffixSubtraction) {
    std::string code = R"(
        s1 = "filename.txt" - ".txt"
        s2 = "no_suffix" - ".txt"
        s3 = "multiple.txt.txt" - ".txt"
        println(s1)
        println(s2)
        println(s3)
    )";
    std::string expected = "filename\nno_suffix\nmultiple.txt\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, StringRepetition) {
    std::string code = R"(
        s1 = "a" * 5
        s2 = "ab" * 3.0
        s3 = "x" * 0
        s4 = "y" * 2.5  
        println(s1)
        println(s2)
        println(s3)
        println(s4)
    )";
    std::string expected = "aaaaa\nababab\n\nyy\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, SingleIndexAccess) {
    std::string code = R"(
        s = "Hello"
        println(s[0])   
        println(s[4])   
        println(s[-1])  
        println(s[-5])  
    )";
    std::string expected = "H\no\no\nH\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, BasicSlicing) {
    std::string code = R"(
        s = "Hello World"
        println(s[:5])   
        println(s[6:])   
        println(s[2:7])  
        println(s[:])    
    )";
    std::string expected = "Hello\nWorld\nllo W\nHello World\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, MixedOperations) {
    std::string code = R"(
        s = ("a" + "b") * 3
        t = s - "b" + "c"
        println(t[::2])
    )";
    std::string expected = "aaa\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, StringLength) {
    std::string code = R"(
        s = "Hello\\tWorld"
        println(len(s)) 
    )";
    std::string expected = "12\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, EmptyStringOperations) {
    std::string code = R"(
        e = ""
        println(e + "text")
        println("text" + e)
        println(e - "suffix")
        println(e * 10)
        println(e[:])
        println(e[1:2])
    )";
    std::string expected = "text\ntext\n\n\n\n\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, SpecialCharacterCases) {
    std::string code = R"(
        s = "\\0\\t\\n\\\"\\\\"
        println(s)
        println(s[0])  
        println(s[1])   
        println(s[2])    
        println(s[3])  
    )";
    std::string expected = "\\0\\t\\n\\\"\\\\\n\\\n0\n\\\nt\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, StringMultiplicationEdgeCases) {
    std::string code = R"(
        println("a" * 0.999)   
        println("b" * -5)      
        println("c" * 1.0)     
        println("d" * 2.999)  
    )";
    std::string expected = "\n\nc\ndd\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, SuffixRemovalEdgeCases) {
    std::string code = R"(
        println("file.txt" - ".txt")
        println("file.txt.txt" - ".txt")
        println("file.txt" - "longer_suffix")
        println("exact" - "exact")
        println("" - "suffix")
        println("prefix" - "")
    )";
    std::string expected = "file\nfile.txt\nfile.txt\n\n\nprefix\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, ConcatenationMixedTypes) {
    std::string code = R"(
        println("Value: " + "42")
        println("Pi: " + "3.14159")
        println("10" + " items")
        println("3.14" + " is pi")
    )";
    std::string expected = "Value: 42\nPi: 3.14159\n10 items\n3.14 is pi\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, StepZeroHandling) {
    std::string code = R"(
        s = "abc"
        println(s[::0]) 
    )";
    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_FALSE(interpret(input, output));
}

TEST(StringOperationsTestSuite, ComplexMixedOperations) {
    std::string code = R"(
        s = ("a" + "b") * 3
        t = s - "b" + "c"
        u = t[::2] * 2
        println(u - "ac")
    )";
    std::string expected = "aaaaaa\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(StringOperationsTestSuite, LargeStringHandling) {
    std::string code = R"(
        s = "a" * 1000000
        println(len(s) == 1000000)
        t = s[999990:]
        println(t == "aaaaaaaaaa")
        u = s - "a" 
        println(len(u) == 999999)
    )";
    std::string expected = "true\ntrue\ntrue\n";
    std::istringstream input(code);
    std::ostringstream output;
    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}