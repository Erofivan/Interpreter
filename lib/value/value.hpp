#ifndef _ITMOSCRIPT_LIB_VALUE_HPP_
#define _ITMOSCRIPT_LIB_VALUE_HPP_

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "ast/ast.hpp"
#include "builtins/std/real_number.hpp"

class Value {
public:
    virtual ~Value() = default;
    virtual std::string ToString() const = 0;
};

using ValuePtr = std::shared_ptr<Value>;

class IntValue : public Value {
public:
    RealNumber value;

    IntValue(const std::string& val);
    IntValue(long long val) : value(val) {}
    IntValue(const RealNumber& val) : value(val) {}

    std::string ToString() const override;
};

class BoolValue : public Value {
public:
    bool value;
    explicit BoolValue(bool val) : value(val) {}
    std::string ToString() const override;
};

class StringValue : public Value {
public:
    std::string value;
    explicit StringValue(const std::string& val) : value(val) {}
    std::string ToString() const override;
};

class ListValue : public Value {
public:
    std::vector<ValuePtr> elements;
    explicit ListValue(std::vector<ValuePtr> elems) : elements(std::move(elems)) {}
    std::string ToString() const override;
};

class NullValue : public Value {
public:
    std::string ToString() const override { return ""; }
};

class FunctionValue : public Value {
public:
    virtual ValuePtr Call(const std::vector<ValuePtr>& args) = 0;

    std::string ToString() const override { return "<function>"; }
};

class UserFunctionValue : public FunctionValue {
public:
    std::vector<std::string> params;
    std::vector<std::unique_ptr<class Stmt>> body;
    std::shared_ptr<class Environment> closure;

    UserFunctionValue(std::vector<std::string> params,
                      std::vector<std::unique_ptr<Stmt>> body,
                      std::shared_ptr<Environment> closure)
        : params(std::move(params)), body(std::move(body)), closure(closure) {}

    ValuePtr Call(const std::vector<ValuePtr>& args) override;
};

class BuiltinFunctionValue : public FunctionValue {
public:
    std::function<ValuePtr(const std::vector<ValuePtr>&)> func;

    BuiltinFunctionValue(std::function<ValuePtr(const std::vector<ValuePtr>&)> func)
        : func(std::move(func)) {}

    ValuePtr Call(const std::vector<ValuePtr>& args) override {
        return func(args);
    }
};

#endif
