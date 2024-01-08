/*

<label declaration> ::=
    <label name> ':'

<label reference> ::=
    '!' <label name>

<mov> ::=
    "mov" <source> ',' <destination>


<source> ::=
    <register>
    | <address>
    | <immediate>

<destination> ::=
    <register>
    | <address>

<address> ::=
    '&' <register>
    | '&' <immediate>

<register> ::=
    r1 | r2 | r3 | r4

<immediate> ::=
    '$' <number>
    | '$' <label reference>

<number> ::=
    <hexadecimal>
    | <decimal>

<hexadecimal> ::=
    '0x' <hexadecimal digit>+

<decimal> ::=
    <decimal digit>+

<hexadecimal digit> ::=
    '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
    | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'

<decimal digit> ::=
    '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
    | '8' | '9'

*/

#include <string>
#include <functional>
#include <iostream>
#include <tuple>

#include "pc.hpp"

using namespace pc;

auto skipSpaces = pc::c::any(pc::p::ch(' '));
auto manySpaces = pc::c::many(pc::p::ch(' '));

auto reg = pc::c::chain(
    pc::p::ch('r'),
    pc::p::dig);

auto mov = pc::c::chain(
    pc::p::str("mov"),
    manySpaces,
    reg,
    skipSpaces,
    pc::p::ch(','),
    skipSpaces,
    reg,
    // pc::c::comaSeparated(reg),
    skipSpaces);

int main()
{
    std::string input = "mov r1, r2";

    std::cout << "Parsing '" << input << "' with mov" << std::endl;
    bool result = mov(input);
    std::cout << "Result: " << result << std::endl;
    std::cout << "Remaining input: '" << input << "'\n";

    std::cout << std::endl;

    std::string input2 = "r1,r2,r3";
    auto sep = pc::c::sepByList(reg, pc::p::ch(','));

    std::cout << "Parsing '" << input2 << "' with sepBy" << std::endl;
    bool result2 = sep(input2);
    std::cout << "Result: " << result2 << std::endl;

    std::cout << std::endl;

    std::string input3 = "r1,r2,r3";
    auto sep2 = pc::c::sepByList(reg, pc::p::ch(','));

    std::cout << "Parsing '" << input3 << "' with sepBy" << std::endl;
    bool result3 = sep2(input3);
    std::cout << "Result: " << result3 << std::endl;

    std::cout << std::endl;

    std::string input4 = "r1,r2,";
    auto sep3 = pc::c::sepBy(2, reg, pc::p::ch(','));
    std::cout << "Parsing '" << input4 << "' with sepBy" << std::endl;
    bool result4 = sep3(input4);
    std::cout << "Result: " << result4 << std::endl;

    std::cout << std::endl;

    std::string input5 = "(r1)";
    auto parens = pc::c::surroundedBy(pc::p::ch('('), reg, pc::p::ch(')'));
    std::cout << "Parsing '" << input5 << "' with surroundedBy" << std::endl;
    bool result5 = parens(input5);
    std::cout << "Result: " << result5 << std::endl;

    std::cout << std::endl;
}
