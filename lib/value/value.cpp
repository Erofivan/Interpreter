#include "value.hpp"
#include "environment/environment.hpp"
#include <stdexcept>

IntValue::IntValue(const std::string& val) {
    value = RealNumber(val);
}

std::string IntValue::ToString() const {
    return value.convert_to<std::string>();
}

std::string BoolValue::ToString() const {
    return value ? "true" : "false";
}

std::string StringValue::ToString() const {
    return value;
}

std::string ListValue::ToString() const {
    std::string res = "[";
    bool first = true;
    for (const auto& elem : elements) {
        if (!first) res += ", ";
        res += elem->ToString();
        first = false;
    }
    res += "]";
    return res;
}

ValuePtr UserFunctionValue::Call(const std::vector<ValuePtr>&) {
    throw std::runtime_error("direct Call of user function is not supported");
}
