#ifndef _ITMOSCRIPT_LIB_ENVIRONMENT_HPP_
#define _ITMOSCRIPT_LIB_ENVIRONMENT_HPP_

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "value/value.hpp"

class Environment {
public:
    Environment(std::shared_ptr<Environment> parent = nullptr)
        : parent_(std::move(parent)) {}

    void SetVariableValue(const std::string& name, std::shared_ptr<Value> value);

    std::shared_ptr<Value> GetVariableValue(const std::string& name) const;

    std::vector<std::string> GetKeyValuesList() const;

private:
    std::unordered_map<std::string, std::shared_ptr<Value>> vars_;
    std::shared_ptr<Environment> parent_;
};

#endif
