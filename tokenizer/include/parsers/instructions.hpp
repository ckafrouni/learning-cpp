#pragma once
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
*/

#include "parsers/primitives.hpp"

namespace pc
{
    namespace c
    {

        auto map = [](Parser parser, auto fn)
        {
            return Parser([parser, fn](const char *input) -> ParserResult
                          {
                auto result = parser(input);
                if (result.success) {
                    auto [value, name] = fn(result.parsed);
                    return {true, result.start, result.end, {name, value}, result.remaining};
                }
                return {false, 0, 0, {}, ""}; },
                          "map");
        };
    }
};

auto kw_mov = pc::p::str("mov");
auto mov = pc::c::map(
    pc::c::chain(
        kw_mov,
        pc::utils::skip_spaces,
        pc::utils::pair(
            primitives::src,
            pc::p::ch(","),
            primitives::dst),
        pc::utils::skip_spaces_opt),
    [](auto &&result)
    {
        return std::make_tuple(std::move(result), "MOV");
    });
// auto kw_push = pc::p::str("push");
// auto push = pc::c::chain(
//     kw_push,
//     pc::utils::skip_spaces,
//     primitives::src,
//     pc::utils::skip_spaces_opt);

// auto kw_pop = pc::p::str("pop");
// auto pop = pc::c::chain(
//     kw_pop,
//     pc::utils::skip_spaces,
//     primitives::dst,
//     pc::utils::skip_spaces_opt);

// auto kw_add = pc::p::str("add");
// auto add = pc::c::chain(
//     kw_add,
//     pc::utils::skip_spaces,
//     pc::utils::pair(
//         primitives::dst,
//         pc::p::ch(","),
//         pc::utils::pair(
//             primitives::src,
//             pc::p::ch(","),
//             primitives::src)),
//     pc::utils::skip_spaces_opt);

// auto kw_sub = pc::p::str("sub");
// auto sub = pc::c::chain(
//     kw_sub,
//     pc::utils::skip_spaces,
//     pc::utils::pair(
//         primitives::dst,
//         pc::p::ch(","),
//         pc::utils::pair(
//             primitives::src,
//             pc::p::ch(","),
//             primitives::src)),
//     pc::utils::skip_spaces_opt);

// auto kw_mul = pc::p::str("mul");
// auto mul = pc::c::chain(
//     kw_mul,
//     pc::utils::skip_spaces,
//     pc::utils::pair(
//         primitives::dst,
//         pc::p::ch(","),
//         pc::utils::pair(
//             primitives::src,
//             pc::p::ch(","),
//             primitives::src)),
//     pc::utils::skip_spaces_opt);

// auto kw_div = pc::p::str("div");
// auto div = pc::c::chain(
//     kw_div,
//     pc::utils::skip_spaces,
//     pc::utils::pair(
//         primitives::dst,
//         pc::p::ch(","),
//         pc::utils::pair(
//             primitives::src,
//             pc::p::ch(","),
//             primitives::src)),
//     pc::utils::skip_spaces_opt);

// auto kw_mod = pc::p::str("mod");
// auto mod = pc::c::chain(
//     kw_mod,
//     pc::utils::skip_spaces,
//     pc::utils::pair(
//         primitives::dst,
//         pc::p::ch(","),
//         pc::utils::pair(
//             primitives::src,
//             pc::p::ch(","),
//             primitives::src)),
//     pc::utils::skip_spaces_opt);

// auto kw_jmp = pc::p::str("jmp");
// auto jmp = pc::c::chain(
//     kw_jmp,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_jeq = pc::p::str("jeq");
// auto jeq = pc::c::chain(
//     kw_jeq,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_jne = pc::p::str("jne");
// auto jne = pc::c::chain(
//     kw_jne,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_jlt = pc::p::str("jlt");
// auto jlt = pc::c::chain(
//     kw_jlt,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_jgt = pc::p::str("jgt");
// auto jgt = pc::c::chain(
//     kw_jgt,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_jle = pc::p::str("jle");
// auto jle = pc::c::chain(
//     kw_jle,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_jge = pc::p::str("jge");
// auto jge = pc::c::chain(
//     kw_jge,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_hlt = pc::p::str("hlt");
// auto hlt = pc::c::chain(
//     kw_hlt,
//     pc::utils::skip_spaces_opt);

// auto kw_call = pc::p::str("call");
// auto call = pc::c::chain(
//     kw_call,
//     pc::utils::skip_spaces,
//     primitives::addr,
//     pc::utils::skip_spaces_opt);

// auto kw_ret = pc::p::str("ret");
// auto ret = pc::c::chain(
//     kw_ret,
//     pc::utils::skip_spaces_opt);

// auto instruction = pc::c::choice(
//     mov,
//     push,
//     pop,
//     add,
//     sub,
//     mul,
//     div,
//     mod,
//     jmp,
//     jeq,
//     jne,
//     jlt,
//     jgt,
//     jle,
//     jge,
//     hlt,
//     call,
//     ret);
