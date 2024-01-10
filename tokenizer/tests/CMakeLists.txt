file(GLOB TESTS *.cpp)

add_executable(tests pc_tests.cpp)
add_test(NAME tests COMMAND tests)
