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

auto digit = pc::c::choice(
    pc::p::ch('0'),
    pc::p::ch('1'),
    pc::p::ch('2'),
    pc::p::ch('3'),
    pc::p::ch('4'),
    pc::p::ch('5'),
    pc::p::ch('6'),
    pc::p::ch('7'),
    pc::p::ch('8'),
    pc::p::ch('9'));

auto hexDigit = pc::c::choice(
    digit,
    pc::p::ch('a'),
    pc::p::ch('b'),
    pc::p::ch('c'),
    pc::p::ch('d'),
    pc::p::ch('e'),
    pc::p::ch('f'));

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
