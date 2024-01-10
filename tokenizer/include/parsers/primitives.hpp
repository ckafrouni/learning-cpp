#pragma once

#include "pc/pc.hpp"
#include "pc/parsers.hpp"
#include "pc/combinators.hpp"
#include "pc/utils.hpp"

/*

<hlt> ::= "hlt"

<call> ::= "call" <addr>
<ret> ::= "ret"

<mov> ::= "mov" <src> ',' <dst>
<push> ::= "push" <src>
<pop> ::= "pop" <dst>

<add> ::= "add" <dst> ',' <src> ',' <src>
<sub> ::= "sub" <dst> ',' <src> ',' <src>
<mul> ::= "mul" <dst> ',' <src> ',' <src>
<div> ::= "div" <dst> ',' <src> ',' <src>
<mod> ::= "mod" <dst> ',' <src> ',' <src>

<jmp> ::= "jmp" <addr>
<jeq> ::= "jeq" <addr>
<jne> ::= "jne" <addr>
<jlt> ::= "jlt" <addr>
<jgt> ::= "jgt" <addr>
<jle> ::= "jle" <addr>
<jge> ::= "jge" <addr>

--

<src> ::=
    <reg>
    | <addr>
    | <lit>

<dst> ::=
    <reg>
    | <addr>

<addr> ::=
    '&' <reg>
    | '&' <lit>
    | '&' <sq_bracketed_expr>

<reg> ::=
    r1 | r2 | r3 | r4

<lit> ::=
    '$' <num>
    | '$' <sq_bracketed_expr>

<num> ::= <hex_num>
<hex_num> ::= '0x' [0-9a-fA-F]+

<sq_bracketed_expr> ::= '[' <expr> ']'

-- Example:
-- [(!label + $0x1)] or [($0x1 + $0x1)] or [!label] or [$0x1]
-- [($0x1 + ($0x2 * $0x3))]
<expr> ::=
    <label_ref>
    | <num>
    | '(' <expr> op <expr> ')'

<op> ::= '+' | '-' | '*' | '/' | '%'

<label_ref> ::= '!' <identifier>
<label_def> ::= <identifier> ':'

<identifier> ::= [a-zA-Z][a-zA-Z0-9_]*

*/

namespace primitives
{
    auto hex_num = pc::c::chain(
        pc::p::str("0x"),
        pc::utils::hex_number,
        pc::utils::skip_spaces_opt);

    auto op = pc::c::choice(
        pc::p::ch("+"),
        pc::p::ch("-"),
        pc::p::ch("*"),
        pc::p::ch("/"),
        pc::p::ch("%"));
    auto reg = pc::p::regex("^[rR][1-4]", "register");
    auto identifier = pc::p::regex("^[a-zA-Z][a-zA-Z0-9_]*", "identifier");

    auto label_def = pc::c::chain(
        identifier,
        pc::utils::skip_spaces_opt,
        pc::p::ch(":"),
        pc::utils::skip_spaces_opt);

    auto label_ref = pc::c::chain(
        pc::p::ch("!"),
        identifier,
        pc::utils::skip_spaces_opt);

    pc::Parser expr([](const char *input)
                    {
    auto sq_bracketed_expr = pc::c::surround(
        pc::c::skip(pc::p::ch("[")),
        expr,
        pc::c::skip(pc::p::ch("]")));

    auto lit = pc::c::chain(
        pc::c::choice(
            hex_num,
            sq_bracketed_expr),
        pc::utils::skip_spaces_opt);
    return pc::c::choice(
        label_ref,
        lit,
        pc::c::surround(
            pc::c::skip(pc::p::ch("(")),
            pc::utils::pair(expr, op, expr),
            pc::c::skip(pc::p::ch(")"))))(input); },
                    "expr");

    auto sq_bracketed_expr = pc::c::surround(
        pc::c::skip(pc::p::ch("[")),
        expr,
        pc::c::skip(pc::p::ch("]")));

    auto lit = pc::c::chain(
        pc::p::ch("$"),
        pc::c::choice(
            hex_num,
            sq_bracketed_expr),
        pc::utils::skip_spaces_opt);

    auto addr = pc::c::chain(
        pc::p::ch("&"),
        pc::c::choice(
            reg,
            sq_bracketed_expr),
        pc::utils::skip_spaces_opt);

    auto src = pc::c::choice(
        reg,
        addr,
        lit);

    auto dst = pc::c::choice(
        reg,
        addr);
} // namespace primitives
