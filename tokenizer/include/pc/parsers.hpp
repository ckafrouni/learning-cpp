#pragma once

#include <vector>
#include <functional>
#include <string>
#include <regex>
#include <iostream>

#include "pc/pc.hpp"

namespace pc
{
    namespace p
    {
        /**
         * Parser that matches the character `c`.
         *
         * @param c The character to match.
         * @return A parser that matches the character `c`.
         */
        auto ch = [](const std::string c) -> pc::ParserR
        {
            if (c.length() != 1)
                throw std::invalid_argument("ch: Expected a single character");
            return [c](std::string input) -> pc::ParserResult
            {
                if (!input.empty() && input[0] == c[0])
                    return {true, 0, 1, {input.substr(0, 1)}, input.substr(1)};
                return {false, 0, 0, {}, ""};
            };
        };

        /**
         * Parser that matches the string `s`.
         *
         * @param s The string to match.
         * @return A parser that matches the string `s`.
         */
        auto str = [](const std::string s) -> pc::ParserR
        {
            return [s](std::string input) -> pc::ParserResult
            {
                if (input.substr(0, s.length()) == s)
                    return {true, 0, s.length(), {input.substr(0, s.length())}, input.substr(s.length())};
                else
                    return {false, 0, 0, {}, ""};
            };
        };

        /**
         * Parser that matches the regular expression `s`.
         *
         * @param s The regular expression to match.
         * @return A parser that matches the regular expression `s`.
         */
        auto regex = [](const std::string s) -> pc::ParserR
        {
            return [s](std::string input) -> pc::ParserResult
            {
                std::regex r(s);
                std::smatch m;
                if (std::regex_search(input, m, r))
                {
                    return {true, 0, static_cast<size_t>(m[0].length()), {m[0]}, input.substr(m[0].length())};
                }
                return {false, 0, 0, {}, ""};
            };
        };
    } // namespace p
}
