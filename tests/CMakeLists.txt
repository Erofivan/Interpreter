include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(itmoscript_interpreter_tests)

add_subdirectory(01_expressions_tests)
add_subdirectory(02_statements_tests)
add_subdirectory(03_operations_tests)
add_subdirectory(05_ifs_and_loops_tests)
add_subdirectory(06_custom_functions_tests)
add_subdirectory(full_time_programs_tests)

target_link_libraries(
  itmoscript_interpreter_tests
  itmoscript_interpreter
  GTest::gtest_main
)

target_include_directories(itmoscript_interpreter_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(itmoscript_interpreter_tests)