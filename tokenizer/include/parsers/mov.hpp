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

#include "pc/pc.hpp"
#include "pc/parsers.hpp"
#include "pc/combinators.hpp"
#include "pc/utils.hpp"

auto reg = pc::p::regex("^[rR][1-4]");
auto identifier = pc::p::regex("^[a-zA-Z][a-zA-Z0-9_]*");

auto label_declaration = pc::c::chain(
    identifier,
    pc::utils::skip_optional_spaces,
    pc::p::ch(":"),
    pc::utils::skip_optional_spaces);

auto label_reference = pc::c::chain(
    pc::p::ch("!"),
    identifier,
    pc::utils::skip_optional_spaces);

auto mov_reg_reg = pc::c::chain(
    pc::p::str("mov"),
    pc::utils::skip_spaces,
    reg,
    pc::utils::skip_optional_spaces,
    pc::p::ch(","),
    pc::utils::skip_optional_spaces,
    reg,
    pc::utils::skip_optional_spaces);
