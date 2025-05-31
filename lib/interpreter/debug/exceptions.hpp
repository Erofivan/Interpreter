#ifndef _ITMOSCRIPT_LIB_EXCEPTIONS_HPP_
#define _ITMOSCRIPT_LIB_EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

class MyError : public std::logic_error {
  public:
    MyError(size_t line, size_t col, const std::string& msg)
        : line_num_(line), col_num_(col),
          std::logic_error(msg) {}

    virtual ~MyError() = default;

    size_t GetLineNum() const noexcept { 
        return line_num_; 
    }

    size_t GetColNum() const noexcept { 
        return col_num_; 
    }

    virtual const char* ErrorType() const noexcept = 0;

  private:
    size_t line_num_;
    size_t col_num_;
};

class LexerError : public MyError {
  public:
    LexerError(size_t line, size_t col, const std::string& msg)
        : MyError(line, col, msg) {}

    const char* ErrorType() const noexcept override { 
        return "LexerError"; 
    }
};

class ParserError : public MyError {
  public:
    ParserError(size_t line, size_t col, const std::string& msg)
        : MyError(line, col, msg) {}

    const char* ErrorType() const noexcept override { 
        return "ParserError"; 
    }
};

class InterpreterError : public MyError {
  public:
    InterpreterError(size_t line, size_t col, const std::string& msg)
        : MyError(line, col, msg) {}

    const char* ErrorType() const noexcept override { 
        return "InterpreterError"; 
    }
};

#endif