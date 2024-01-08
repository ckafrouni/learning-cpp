#pragma once
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

#include "pc.hpp"

auto skipSpaces = pc::p::regex("^[ \t]*");
auto manySpaces = pc::p::regex("^[ \t]+");

auto digit = pc::p::regex("^[0-9]");
auto hexDigit = pc::p::regex("^[0-9a-fA-F]");
auto reg = pc::p::regex("^[rR][1-4]");
auto identifier = pc::p::regex("^[a-zA-Z][a-zA-Z0-9_]*");

auto label_declaration = pc::c::chain(
    identifier,
    skipSpaces,
    pc::p::ch(':'));

auto label_reference = pc::c::chain(
    pc::p::ch('!'),
    identifier);

auto mov_reg_reg = pc::c::chain(
    pc::p::str("mov"),
    manySpaces,
    reg,
    skipSpaces,
    pc::p::ch(','),
    skipSpaces,
    reg,
    skipSpaces);
