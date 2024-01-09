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
        auto spaces = pc::p::regex("^[ \t]+");
        auto optional_spaces = pc::c::optional(spaces);

        auto skip_spaces = pc::c::skip(spaces);
        auto skip_optional_spaces = pc::c::skip(optional_spaces);

        auto digit = pc::p::regex("^[0-9]");
        auto hexDigit = pc::p::regex("^[0-9a-fA-F]");

    } // namespace utils
} // namespace pc
