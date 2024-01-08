#include <string>
#include <iostream>

#include "pc.hpp"
#include "parsers/mov.hpp"

int main()
{
    std::string input = "1";
    std::cout << "Parsing '" << input << "' with digit" << std::endl;
    bool result = digit(input);

    // std::string input = "mov r1, r2";

    // std::cout << "Parsing '" << input << "' with mov" << std::endl;
    // bool result = mov(input);
    // std::cout << "Result: " << result << std::endl;
    // std::cout << "Remaining input: '" << input << "'\n";

    // std::cout << std::endl;

    // std::string input2 = "r1,r2,r3";
    // auto sep = pc::c::sepByList(reg, pc::p::ch(','));

    // std::cout << "Parsing '" << input2 << "' with sepBy" << std::endl;
    // bool result2 = sep(input2);
    // std::cout << "Result: " << result2 << std::endl;

    // std::cout << std::endl;

    // std::string input3 = "r1,r2,r3";
    // auto sep2 = pc::c::sepByList(reg, pc::p::ch(','));

    // std::cout << "Parsing '" << input3 << "' with sepBy" << std::endl;
    // bool result3 = sep2(input3);
    // std::cout << "Result: " << result3 << std::endl;

    // std::cout << std::endl;

    // std::string input4 = "r1,r2,";
    // auto sep3 = pc::c::sepBy(2, reg, pc::p::ch(','));
    // std::cout << "Parsing '" << input4 << "' with sepBy" << std::endl;
    // bool result4 = sep3(input4);
    // std::cout << "Result: " << result4 << std::endl;

    // std::cout << std::endl;

    // std::string input5 = "(r1)";
    // auto parens = pc::c::surroundedBy(pc::p::ch('('), reg, pc::p::ch(')'));
    // std::cout << "Parsing '" << input5 << "' with surroundedBy" << std::endl;
    // bool result5 = parens(input5);
    // std::cout << "Result: " << result5 << std::endl;

    // std::cout << std::endl;
}
