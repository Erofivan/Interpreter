// builtins.cpp
#include "builtins.hpp"
#include "value/value.hpp"
#include "builtins/std/real_number.hpp"
#include "environment/environment.hpp"
#include <iostream>
#include <algorithm>
#include <regex>

ValuePtr print(const std::vector<ValuePtr>& args, std::ostream& out) {
    for (const auto& arg : args) {
        out << arg->ToString();
    }
    return std::make_shared<NullValue>();
}

ValuePtr println(const std::vector<ValuePtr>& args, std::ostream& out) {
    for (const auto& arg : args) {
        out << arg->ToString();
    }
    out << std::endl;
    return std::make_shared<NullValue>();
}

ValuePtr len(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) {
        throw std::runtime_error("len() takes one argument");
    }
    if (auto str = std::dynamic_pointer_cast<StringValue>(args[0])) {
        return std::make_shared<IntValue>(std::to_string(str->value.size()));
    }
    if (auto list = std::dynamic_pointer_cast<ListValue>(args[0])) {
        return std::make_shared<IntValue>(std::to_string(list->elements.size()));
    }
    throw std::runtime_error("len() argument must be string or list");
}

ValuePtr range(const std::vector<ValuePtr>& args) {
    if (args.size() < 1 || args.size() > 3) {
        throw std::runtime_error("range() expects 1, 2, or 3 arguments");
    }

    for (const auto& arg : args) {
        if (!std::dynamic_pointer_cast<IntValue>(arg)) {
            throw std::runtime_error("range() arguments must be integers");
        }
    }

    RealNumber start, end, step;
    auto to_cpp_int = [](const ValuePtr& v) {
        return std::dynamic_pointer_cast<IntValue>(v)->value;
    };
    
    if (args.size() == 1) {
        start = 0;
        end = to_cpp_int(args[0]);
        step = 1;
    } else if (args.size() == 2) {
        start = to_cpp_int(args[0]);
        end = to_cpp_int(args[1]);
        step = 1;
    } else { 
        start = to_cpp_int(args[0]);
        end = to_cpp_int(args[1]);
        step = to_cpp_int(args[2]);
    }

    if (step == 0) {
        throw std::runtime_error("range() step must not be zero");
    }

    std::vector<ValuePtr> elems;
    if (step > 0) {
        for (RealNumber i = start; i < end; i += step) {
            elems.push_back(std::make_shared<IntValue>(i.convert_to<std::string>()));
        }
    } else {
        for (RealNumber i = start; i > end; i += step) {
            elems.push_back(std::make_shared<IntValue>(i.convert_to<std::string>()));
        }
    }

    return std::make_shared<ListValue>(elems);
}

ValuePtr builtin_abs(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("abs() requires one argument");
    auto num = std::dynamic_pointer_cast<IntValue>(args[0]);
    if (!num) throw std::runtime_error("abs() requires a number");
    return std::make_shared<IntValue>(num->value.abs());
}

ValuePtr builtin_ceil(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("ceil() requires one argument");
    auto num = std::dynamic_pointer_cast<IntValue>(args[0]);
    if (!num) throw std::runtime_error("ceil() requires a number");
    return std::make_shared<IntValue>(num->value.ceil());
}

ValuePtr builtin_floor(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("floor() requires one argument");
    auto num = std::dynamic_pointer_cast<IntValue>(args[0]);
    if (!num) throw std::runtime_error("floor() requires a number");
    return std::make_shared<IntValue>(num->value.floor());
}

ValuePtr builtin_round(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("round() requires one argument");
    auto num = std::dynamic_pointer_cast<IntValue>(args[0]);
    if (!num) throw std::runtime_error("round() requires a number");
    return std::make_shared<IntValue>(num->value.round());
}

ValuePtr builtin_sqrt(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("sqrt() requires one argument");
    auto num = std::dynamic_pointer_cast<IntValue>(args[0]);
    if (!num) throw std::runtime_error("sqrt() requires a number");
    try {
        return std::make_shared<IntValue>(num->value.sqrt());
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

ValuePtr builtin_rnd(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("rnd() requires one argument");
    auto num = std::dynamic_pointer_cast<IntValue>(args[0]);
    if (!num) throw std::runtime_error("rnd() requires a number");
    if (num->value < RealNumber(0)) 
        throw std::runtime_error("rnd() requires non-negative integer");
    
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    
    long long n = static_cast<long long>(num->value);
    int r = rand() % n;
    return std::make_shared<IntValue>(RealNumber(r));
}

ValuePtr builtin_parse_num(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("parse_num() requires one argument");
    auto str_val = std::dynamic_pointer_cast<StringValue>(args[0]);
    if (!str_val) throw std::runtime_error("parse_num() requires a string");
    
    try {
        RealNumber num(str_val->value);
        return std::make_shared<IntValue>(num);
    } catch (...) {
        return std::make_shared<NullValue>();
    }
}

ValuePtr builtin_to_string(const std::vector<ValuePtr>& args) {
    if (args.size() != 1) throw std::runtime_error("to_string() requires one argument");
    return std::make_shared<StringValue>(args[0]->ToString());
}

ValuePtr builtin_lower(const std::vector<ValuePtr>& args) {
    if (args.size() != 1)
        throw std::runtime_error("lower() takes one argument");

    auto str = std::dynamic_pointer_cast<StringValue>(args[0]);
    if (!str)
        throw std::runtime_error("lower() argument must be a string");

    std::string result = str->value;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return std::make_shared<StringValue>(result);
}

ValuePtr builtin_upper(const std::vector<ValuePtr>& args) {
    if (args.size() != 1)
        throw std::runtime_error("upper() takes one argument");

    auto str = std::dynamic_pointer_cast<StringValue>(args[0]);
    if (!str)
        throw std::runtime_error("upper() argument must be a string");

    std::string result = str->value;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return std::make_shared<StringValue>(result);
}

// split(s, delim)
ValuePtr builtin_split(const std::vector<ValuePtr>& args) {
    if (args.size() != 2)
        throw std::runtime_error("split() takes two arguments");

    auto str = std::dynamic_pointer_cast<StringValue>(args[0]);
    auto delim = std::dynamic_pointer_cast<StringValue>(args[1]);
    if (!str || !delim)
        throw std::runtime_error("split() arguments must be strings");

    std::vector<ValuePtr> result;
    size_t pos = 0, found;
    while ((found = str->value.find(delim->value, pos)) != std::string::npos) {
        result.push_back(std::make_shared<StringValue>(str->value.substr(pos, found - pos)));
        pos = found + delim->value.length();
    }
    result.push_back(std::make_shared<StringValue>(str->value.substr(pos)));
    return std::make_shared<ListValue>(result);
}

// join(list, delim)
ValuePtr builtin_join(const std::vector<ValuePtr>& args) {
    if (args.size() != 2)
        throw std::runtime_error("join() takes two arguments");

    auto list = std::dynamic_pointer_cast<ListValue>(args[0]);
    auto delim = std::dynamic_pointer_cast<StringValue>(args[1]);
    if (!list || !delim)
        throw std::runtime_error("join() requires (list, string)");

    std::string result;
    for (size_t i = 0; i < list->elements.size(); ++i) {
        if (i > 0) result += delim->value;
        result += list->elements[i]->ToString();
    }
    return std::make_shared<StringValue>(result);
}

// replace(s, old, new)
ValuePtr builtin_replace(const std::vector<ValuePtr>& args) {
    if (args.size() != 3)
        throw std::runtime_error("replace() takes three arguments");

    auto str = std::dynamic_pointer_cast<StringValue>(args[0]);
    auto old_s = std::dynamic_pointer_cast<StringValue>(args[1]);
    auto new_s = std::dynamic_pointer_cast<StringValue>(args[2]);
    if (!str || !old_s || !new_s)
        throw std::runtime_error("replace() requires string arguments");

    std::string result = str->value;
    size_t pos = 0;
    while ((pos = result.find(old_s->value, pos)) != std::string::npos) {
        result.replace(pos, old_s->value.length(), new_s->value);
        pos += new_s->value.length();
    }
    return std::make_shared<StringValue>(result);
}

// push(list, x)
ValuePtr builtin_push(const std::vector<ValuePtr>& args) {
    if (args.size() != 2)
        throw std::runtime_error("push() takes two arguments");

    auto list = std::dynamic_pointer_cast<ListValue>(args[0]);
    if (!list)
        throw std::runtime_error("push() first argument must be a list");

    list->elements.push_back(args[1]);
    return std::make_shared<NullValue>();
}

// pop(list)
ValuePtr builtin_pop(const std::vector<ValuePtr>& args) {
    if (args.size() != 1)
        throw std::runtime_error("pop() takes one argument");

    auto list = std::dynamic_pointer_cast<ListValue>(args[0]);
    if (!list)
        throw std::runtime_error("pop() argument must be a list");

    if (list->elements.empty())
        throw std::runtime_error("pop() from empty list");

    auto val = list->elements.back();
    list->elements.pop_back();
    return val;
}

// insert(list, index, x)
ValuePtr builtin_insert(const std::vector<ValuePtr>& args) {
    if (args.size() != 3)
        throw std::runtime_error("insert() takes three arguments");

    auto list = std::dynamic_pointer_cast<ListValue>(args[0]);
    auto index = std::dynamic_pointer_cast<IntValue>(args[1]);
    if (!list || !index)
        throw std::runtime_error("insert() requires (list, int, value)");

    auto idx = static_cast<size_t>(index->value.convert_to<int>());
    if (idx > list->elements.size())
        throw std::runtime_error("insert() index out of range");

    list->elements.insert(list->elements.begin() + idx, args[2]);
    return std::make_shared<NullValue>();
}

// remove(list, index)
ValuePtr builtin_remove(const std::vector<ValuePtr>& args) {
    if (args.size() != 2)
        throw std::runtime_error("remove() takes two arguments");

    auto list = std::dynamic_pointer_cast<ListValue>(args[0]);
    auto index = std::dynamic_pointer_cast<IntValue>(args[1]);
    if (!list || !index)
        throw std::runtime_error("remove() requires (list, int)");

    auto idx = static_cast<size_t>(index->value.convert_to<int>());
    if (idx >= list->elements.size())
        throw std::runtime_error("remove() index out of range");

    list->elements.erase(list->elements.begin() + idx);
    return std::make_shared<NullValue>();
}
ValuePtr builtin_sort(const std::vector<ValuePtr>& args) {
    if (args.size() != 1)
        throw std::runtime_error("sort() takes one argument");

    auto list = std::dynamic_pointer_cast<ListValue>(args[0]);
    if (!list)
        throw std::runtime_error("sort() requires a list");

    if (list->elements.empty())
        return std::make_shared<NullValue>();  // nothing to sort

    auto first = list->elements[0];

    // Determine type
    bool all_int = std::dynamic_pointer_cast<IntValue>(first) != nullptr;
    bool all_string = std::dynamic_pointer_cast<StringValue>(first) != nullptr;

    for (const auto& el : list->elements) {
        if (all_int && !std::dynamic_pointer_cast<IntValue>(el)) {
            throw std::runtime_error("sort() requires all elements to be of the same type");
        }
        if (all_string && !std::dynamic_pointer_cast<StringValue>(el)) {
            throw std::runtime_error("sort() requires all elements to be of the same type");
        }
        if (!all_int && !all_string) {
            throw std::runtime_error("sort() requires all elements to be of the same type");
        }
    }

    if (all_int) {
        std::sort(list->elements.begin(), list->elements.end(),
            [](const ValuePtr& a, const ValuePtr& b) {
                auto a_int = std::dynamic_pointer_cast<IntValue>(a);
                auto b_int = std::dynamic_pointer_cast<IntValue>(b);
                return a_int->value < b_int->value;
            });
    } else if (all_string) {
        std::sort(list->elements.begin(), list->elements.end(),
            [](const ValuePtr& a, const ValuePtr& b) {
                auto a_str = std::dynamic_pointer_cast<StringValue>(a);
                auto b_str = std::dynamic_pointer_cast<StringValue>(b);
                return a_str->value < b_str->value;
            });
    }

    return std::make_shared<NullValue>();
}

ValuePtr builtin_read(const std::vector<ValuePtr>& args) {
    if (!args.empty()) {
        throw std::runtime_error("read() takes no arguments");
    }

    std::string input;
    std::getline(std::cin, input);

    try {
        RealNumber num(input);
        return std::make_shared<IntValue>(num);
    } catch (...) {}

    static std::regex list_pattern(R"(^\[\s*(.*?)\s*\]$)");
    std::smatch match;
    if (std::regex_match(input, match, list_pattern)) {
        std::string content = match[1]; 

        std::vector<ValuePtr> elements;
        std::stringstream ss(content);
        std::string token;

        while (std::getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t\n\r"));
            token.erase(token.find_last_not_of(" \t\n\r") + 1);

            if (token.empty()) {
                continue;
            }

            try {
                RealNumber num(token);
                elements.push_back(std::make_shared<IntValue>(num));
            } catch (...) {
                elements.push_back(std::make_shared<StringValue>(token));
            }
        }

        return std::make_shared<ListValue>(elements);
    }

    return std::make_shared<StringValue>(input);
}


void registerBuiltins(std::shared_ptr<Environment> env, std::ostream& out) {
    env->SetVariableValue("print",   std::make_shared<BuiltinFunctionValue>(
        [&out](const std::vector<ValuePtr>& args){ return print(args, out); }));
    env->SetVariableValue("println", std::make_shared<BuiltinFunctionValue>(
        [&out](const std::vector<ValuePtr>& args){ return println(args, out); }));
    env->SetVariableValue("len",     std::make_shared<BuiltinFunctionValue>(len));
    env->SetVariableValue("range",   std::make_shared<BuiltinFunctionValue>(range));
    env->SetVariableValue("abs", std::make_shared<BuiltinFunctionValue>(builtin_abs));
    env->SetVariableValue("ceil", std::make_shared<BuiltinFunctionValue>(builtin_ceil));
    env->SetVariableValue("floor", std::make_shared<BuiltinFunctionValue>(builtin_floor));
    env->SetVariableValue("round", std::make_shared<BuiltinFunctionValue>(builtin_round));
    env->SetVariableValue("sqrt", std::make_shared<BuiltinFunctionValue>(builtin_sqrt));
    env->SetVariableValue("rnd", std::make_shared<BuiltinFunctionValue>(builtin_rnd));
    env->SetVariableValue("parse_num", std::make_shared<BuiltinFunctionValue>(builtin_parse_num));
    env->SetVariableValue("to_string", std::make_shared<BuiltinFunctionValue>(builtin_to_string));
    env->SetVariableValue("lower", std::make_shared<BuiltinFunctionValue>(builtin_lower));
    env->SetVariableValue("upper", std::make_shared<BuiltinFunctionValue>(builtin_upper));
    env->SetVariableValue("split", std::make_shared<BuiltinFunctionValue>(builtin_split));
    env->SetVariableValue("join", std::make_shared<BuiltinFunctionValue>(builtin_join));
    env->SetVariableValue("replace", std::make_shared<BuiltinFunctionValue>(builtin_replace));
    env->SetVariableValue("push", std::make_shared<BuiltinFunctionValue>(builtin_push));
    env->SetVariableValue("pop", std::make_shared<BuiltinFunctionValue>(builtin_pop));
    env->SetVariableValue("insert", std::make_shared<BuiltinFunctionValue>(builtin_insert));
    env->SetVariableValue("remove", std::make_shared<BuiltinFunctionValue>(builtin_remove));
    env->SetVariableValue("sort", std::make_shared<BuiltinFunctionValue>(builtin_sort));
    env->SetVariableValue("read", std::make_shared<BuiltinFunctionValue>(builtin_read));
}
