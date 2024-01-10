// #pragma once
// /*

// <label_def> ::=
//     <label name> ':'

// <label_ref> ::=
//     '!' <label name>

// <mov> ::=
//     "mov" <src> ',' <dst>

// <src> ::=
//     <reg>
//     | <addr>
//     | <lit>

// <dst> ::=
//     <reg>
//     | <addr>

// <addr> ::=
//     '&' <reg>
//     | '&' <lit>

// <reg> ::=
//     r1 | r2 | r3 | r4

// <lit> ::=
//     '$' <num>
//     | '$' <label_ref>

// <num> ::=
//     <hex_num>
//     | <decimal>

// <hex_num> ::=
//     '0x' <hex_num digit>+

// <decimal> ::=
//     <decimal digit>+

// <hex_num digit> ::=
//     '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
//     | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'

// <decimal digit> ::=
//     '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
//     | '8' | '9'

// */

// #include "pc/pc.hpp"
// #include "pc/parsers.hpp"
// #include "pc/combinators.hpp"
// #include "pc/utils.hpp"

// #include "parsers/primitives.hpp"

// auto kw_mov = pc::p::str("mov");

// /*

// <mov> ::=
//     "mov" <src> ',' <dst>

// <src> ::=
//     <reg>
//     | <addr>
//     | <lit>

// <dst> ::=
//     <reg>
//     | <addr>

// <addr> ::=
//     '&' <reg>
//     | '&' <lit>

// <reg> ::=
//     r1 | r2 | r3 | r4

// <lit> ::=
//     '$' <num>
//     | '$' <sq_bracketed_expr>

// <num> ::= <hex_num>
// <hex_num> ::= '0x' [0-9a-fA-F]+

// <sq_bracketed_expr> ::= '[' <expr> ']'

// -- Example:
// <expr> ::=
//     <label_ref>
//     | <num>
//     | '(' <expr> op <expr> ')'

// <op> ::= '+' | '-' | '*' | '/' | '%'
// */

// auto mov_reg_reg = pc::c::chain(
//     kw_mov,
//     pc::utils::skip_spaces,
//     pc::utils::pair(reg, pc::p::ch(","), reg),
//     pc::utils::skip_spaces_opt);

// auto mov_reg_address = pc::c::chain(
//     kw_mov,
//     pc::utils::skip_spaces,
//     pc::utils::pair(reg, pc::p::ch(","), addr),
//     pc::utils::skip_spaces_opt);
