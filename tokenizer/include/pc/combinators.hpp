#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <tuple>
#include <regex>
#include <vector>

#include "pc/pc.hpp"

namespace pc
{
    namespace c
    {
        template <typename... Parsers>
        auto chain(Parsers... parsers) -> pc::ParserR
        {
            return [parsers = std::make_tuple(parsers...)](const char *input) mutable
            {
                size_t start = 0;
                std::vector<std::string> value;
                std::string remaining = input;

                return std::apply([&](auto &...args)
                                  {
            bool success = (... && [&](auto &parser) {
                pc::ParserResult result = parser(remaining.c_str());
                if (result.success) {
                    start = (start == 0) ? result.start : start;
                    value.insert(value.end(), result.parsed.begin(), result.parsed.end());
                    remaining = result.remaining;
                    return true;
                }
                return false;
            }(args));
            
            size_t end = start + value.size();
            return pc::ParserResult{success, start, end, value, remaining}; },
                                  parsers);
            };
        }

        /**
         * Parser that doesn't collect the result of the parser `parser`.
         *
         * @param parser The parser to skip.
         * @return A parser that skips the parser `parser`.
         */
        auto skip = [](pc::ParserR parser) -> pc::ParserR
        {
            return [parser](const char *input) -> pc::ParserResult
            {
                pc::ParserResult result = parser(input);
                if (result.success)
                {
                    result.parsed.clear();
                }
                return result;
            };
        };

        /**
         * Parser that succeeds even if the parser `parser` fails.
         *
         * @param parser The parser to try.
         * @return A parser that tries the parser `parser`.
         */
        auto optional = [](pc::ParserR parser) -> pc::ParserR
        {
            return [parser](const char *input) -> pc::ParserResult
            {
                pc::ParserResult result = parser(input);
                if (!result.success)
                {
                    result.success = true;
                    result.start = 0;
                    result.end = 0;
                    result.parsed = {};
                    result.remaining = input;
                }
                return result;
            };
        };
    } // namespace c
} // namespace pc
