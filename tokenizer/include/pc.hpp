#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <tuple>
#include <regex>
#include <vector>

namespace pc
{
    /**
     * Result of a parser.
     *
     * @param success Whether the parser succeeded.
     * @param start The start index of the match.
     * @param end The end index of the match.
     * @param parsed The parsed values.
     * @param remaining The remaining string after parsing.
     */
    struct ParserResult
    {
        bool success;
        size_t start;
        size_t end;
        std::vector<std::string> parsed;
        std::string remaining;
    };

    /**
     * Type for the parser function that returns a `ParserResult`.
     *
     * @param str The string to parse.
     * @return The result of the parser.
     */
    using ParserR = std::function<ParserResult(const char *)>;

    namespace p
    {
        /**
         * Parser that matches the character `c`.
         *
         * @param c The character to match.
         * @return A parser that matches the character `c`.
         */
        auto ch = [](const std::string c) -> ParserR
        {
            if (c.length() != 1)
                throw std::invalid_argument("ch: Expected a single character");
            return [c](std::string input) -> ParserResult
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
        auto regex = [](const std::string s) -> ParserR
        {
            return [s](std::string input) -> ParserResult
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

    namespace c
    {
        template <typename... Parsers>
        auto chain(Parsers... parsers) -> ParserR
        {
            return [parsers = std::make_tuple(parsers...)](const char *input) mutable
            {
                size_t start = 0;
                std::vector<std::string> value;
                std::string remaining = input;

                return std::apply([&](auto &...args)
                                  {
            bool success = (... && [&](auto &parser) {
                ParserResult result = parser(remaining.c_str());
                if (result.success) {
                    start = (start == 0) ? result.start : start;
                    value.insert(value.end(), result.parsed.begin(), result.parsed.end());
                    remaining = result.remaining;
                    return true;
                }
                return false;
            }(args));
            
            size_t end = start + value.size();
            return ParserResult{success, start, end, value, remaining}; },
                                  parsers);
            };
        }

        /**
         * Parser that doesn't collect the result of the parser `parser`.
         *
         * @param parser The parser to skip.
         * @return A parser that skips the parser `parser`.
         */
        auto skip = [](ParserR parser) -> ParserR
        {
            return [parser](const char *input) -> ParserResult
            {
                ParserResult result = parser(input);
                if (result.success)
                {
                    result.parsed.clear();
                }
                return result;
            };
        };

        /**
         * Parser that doesn't collect the result of the parser `parser`
         * and succeeds even if the parser `parser` fails.
         *
         * @param parser The parser to skip.
         * @return A parser that skips the parser `parser`.
         */
        auto skipMaybe = [](ParserR parser) -> ParserR
        {
            return [parser](const char *input) -> ParserResult
            {
                ParserResult result = parser(input);
                if (result.success)
                {
                    result.parsed.clear();
                }
                else
                {
                    result.success = true;
                }
                return result;
            };
        };

    } // namespace c
} // namespace pc
