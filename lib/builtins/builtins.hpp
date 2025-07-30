// builtins.hpp
#ifndef _ITMOSCRIPT_BUILTINS_HPP_
#define _ITMOSCRIPT_BUILTINS_HPP_

#include <vector>
#include "value/value.hpp"

ValuePtr print(const std::vector<ValuePtr>& args, std::ostream& out);
ValuePtr println(const std::vector<ValuePtr>& args, std::ostream& out);
ValuePtr len(const std::vector<ValuePtr>& args);
ValuePtr range(const std::vector<ValuePtr>& args);
ValuePtr builtin_abs(const std::vector<ValuePtr>& args);
ValuePtr builtin_ceil(const std::vector<ValuePtr>& args);
ValuePtr builtin_floor(const std::vector<ValuePtr>& args);
ValuePtr builtin_round(const std::vector<ValuePtr>& args);
ValuePtr builtin_sqrt(const std::vector<ValuePtr>& args);
ValuePtr builtin_rnd(const std::vector<ValuePtr>& args);
ValuePtr builtin_parse_num(const std::vector<ValuePtr>& args);
ValuePtr builtin_to_string(const std::vector<ValuePtr>& args);
ValuePtr builtin_lower(const std::vector<ValuePtr>& args);
ValuePtr builtin_upper(const std::vector<ValuePtr>& args);
ValuePtr builtin_split(const std::vector<ValuePtr>& args);
ValuePtr builtin_join(const std::vector<ValuePtr>& args);
ValuePtr builtin_replace(const std::vector<ValuePtr>& args);
ValuePtr builtin_push(const std::vector<ValuePtr>& args);
ValuePtr builtin_pop(const std::vector<ValuePtr>& args);
ValuePtr builtin_insert(const std::vector<ValuePtr>& args);
ValuePtr builtin_remove(const std::vector<ValuePtr>& args);
ValuePtr builtin_sort(const std::vector<ValuePtr>& args);
ValuePtr builtin_read(const std::vector<ValuePtr>& args);

void registerBuiltins(std::shared_ptr<Environment> env, std::ostream& out);

#endif  // _ITMOSCRIPT_BUILTINS_HPP_
