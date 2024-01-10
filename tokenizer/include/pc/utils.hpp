#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <tuple>
#include <regex>
#include <vector>

#include "pc/pc.hpp"
#include "pc/parsers.hpp"
#include "pc/combinators.hpp"

namespace pc
{
    namespace utils
    {
        auto spaces = pc::p::regex("^[ \t]+", "spaces");
        auto optional_spaces = pc::c::optional(spaces);

        auto skip_spaces = pc::c::skip(spaces);
        auto skip_spaces_opt = pc::c::skip(optional_spaces);

        auto digit = pc::p::regex("^[0-9]", "digit");
        auto hex_digit = pc::p::regex("^[0-9a-fA-F]", "hex digit");
        auto num = pc::p::regex("^[0-9]+", "number");
        auto hex_number = pc::p::regex("^[0-9a-fA-F]+", "hex number");

        auto pair = [](auto a, auto sep, auto b)
        {
            return pc::c::chain(
                a,
                pc::utils::skip_spaces_opt,
                pc::c::skip(sep),
                pc::utils::skip_spaces_opt,
                b,
                pc::utils::skip_spaces_opt);
        };
    } // namespace utils
} // namespace pc
