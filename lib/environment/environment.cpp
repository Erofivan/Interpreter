#include "environment.hpp"

void Environment::SetVariableValue(const std::string& name, std::shared_ptr<Value> value) {
    vars_[name] = value;
}

std::shared_ptr<Value> Environment::GetVariableValue(const std::string& name) const {
    auto it = vars_.find(name);

    if (it != vars_.end()) {
        return it->second;
    }

    if (parent_) {
        return parent_->GetVariableValue(name);
    }



    throw std::runtime_error("name '" + name + "' is not defined");
}

std::vector<std::string> Environment::GetKeyValuesList() const {
    std::vector<std::string> result;

    for (const auto& kv : vars_) {
        result.push_back(kv.first);
    }

    return result;
}
