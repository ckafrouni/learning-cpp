#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <tuple>
#include <regex>

namespace pc
{
    /**
     * Type for the parser function.
     *
     * @param str The string to parse.
     * @return Whether the parser succeeded.
     */
    using Parser = std::function<bool(std::string &)>;

    /**
     * Result of a parser.
     *
     * @param success Whether the parser succeeded.
     * @param start The start index of the match.
     * @param end The end index of the match.
     * @param value The value of the match.
     */
    struct ParserResult
    {
        bool success;
        size_t start;
        size_t end;
        std::string parsed;
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
                    return {true, 0, 1, input.substr(0, 1), input.substr(1)};
                return {false, 0, 0, "", ""};
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
                    return {true, 0, s.length(), input.substr(0, s.length()), input.substr(s.length())};
                else
                    return {false, 0, 0, "", ""};
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
                    return {true, 0, static_cast<size_t>(m[0].length()), m[0], input.substr(m[0].length())};
                }
                return {false, 0, 0, "", ""};
            };
        };

    } // namespace p

    namespace c
    {
        /**
         * Parser that applies the parsers `parsers` in order.
         *
         * @param parsers The parsers to apply in order.
         * @return A parser that applies the parsers `parsers` in order.
         */
        template <typename... Parsers>
        auto choice(Parsers... parsers) -> Parser
        {
            return [parsers = std::make_tuple(parsers...)](std::string &input) mutable
            {
                return std::apply([&](auto &...args)
                                  { return (... || (std::cout << "choiceParser: Applying parser on input '" << input << "'\n", args(input))); },
                                  parsers);
            };
        };

        template <typename... Parsers>
        auto chain(Parsers... parsers) -> ParserR
        {
            return [parsers = std::make_tuple(parsers...)](const char *input) mutable
            {
                size_t start = 0;
                std::string value;
                std::string remaining = input;

                return std::apply([&](auto &...args)
                                  {
            bool success = (... && [&](auto &parser) {
                ParserResult result = parser(remaining.c_str());
                if (result.success) {
                    start = (start == 0) ? result.start : start;
                    value += result.parsed;
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
         * Parser that applies the parser `parser` one or more times.
         *
         * @param parser The parser to apply one or more times.
         * @return A parser that applies the parser `parser` one or more times.
         */
        auto many = [](Parser parser) -> Parser
        {
            return [parser](std::string &input)
            {
                std::string original = input;
                while (!input.empty() && parser(input))
                {
                    std::cout << "oneOrMore: Current input after parser application: '" << input << "'\n";
                }
                bool consumed = original != input;
                std::cout << "oneOrMore: Consumed input? " << consumed << "\n";
                return consumed;
            };
        };

        /**
         * Parser that applies and skips the parser `parser` one or more times.
         *
         * @param parser The parser to apply and skip one or more times.
         * @return A parser that applies and skips the parser `parser` one or more times.
         */
        auto skipMany = [](Parser parser) -> Parser
        {
            return [parser](std::string &input)
            {
                std::string original = input;
                while (!input.empty() && parser(input))
                {
                    std::cout << "skipOneOrMore: Current input after parser application: '" << input << "'\n";
                }
                bool consumed = original != input;
                std::cout << "skipOneOrMore: Consumed input? " << consumed << "\n";
                return consumed;
            };
        };

        /**
         * Parser that applies the parser `parser` zero or more times.
         *
         * @param parser The parser to apply zero or more times.
         * @return A parser that applies the parser `parser` zero or more times.
         */
        auto any = [](Parser parser) -> Parser
        {
            return [parser](std::string &input)
            {
                std::string original = input;
                while (!input.empty() && parser(input))
                {
                    std::cout << "zeroOrMore: Current input after parser application: '" << input << "'\n";
                }
                bool consumed = original != input;
                std::cout << "zeroOrMore: Consumed input? " << consumed << "\n";
                return true;
            };
        };

        /**
         * Parser that applies and skips the parser `parser` zero or more times.
         *
         * @param parser The parser to apply and skip zero or more times.
         * @return A parser that applies and skips the parser `parser` zero or more times.
         */
        auto skipAny = [](Parser parser) -> Parser
        {
            return [parser](std::string &input)
            {
                std::string original = input;
                while (!input.empty() && parser(input))
                {
                    std::cout << "skipZeroOrMore: Current input after parser application: '" << input << "'\n";
                }
                bool consumed = original != input;
                std::cout << "skipZeroOrMore: Consumed input? " << consumed << "\n";
                return true;
            };
        };

        /**
         * Parser that applies the parser `parser` one or more times separated by the parser `separator`.
         *
         * @param parser The parser to apply one or more times.
         * @param separator The parser to apply between each application of `parser`.
         * @return A parser that applies the parser `parser` one or more times separated by the parser `separator`.
         */
        auto sepByList = [](Parser parser, Parser separator) -> Parser
        {
            return [parser, separator](std::string &input)
            {
                std::string original = input;
                while (!input.empty() && parser(input))
                {
                    std::cout << "sepBy: Current input after parser application: '" << input << "'\n";
                    if (!input.empty() && !separator(input))
                    {
                        std::cout << "sepBy: Separator not found\n";
                        return false;
                    }
                }
                bool consumed = original != input;
                std::cout << "sepBy: Consumed input? " << consumed << "\n";
                return consumed;
            };
        };

        /**
         * Parser that applies the parser `parser` `n` times separated by the parser `separator`.
         *
         * @param n The number of times to apply the parser `parser`.
         * @param parser The parser to apply `n`.
         * @param separator The parser to apply between each application of `parser`.
         * @return A parser that applies the parser `parser` `n` times separated by the parser `separator`.
         */
        auto sepBy = [](int n, Parser parser, Parser separator) -> Parser
        {
            return [n, parser, separator](std::string &input)
            {
                std::string original = input;
                for (int i = 0; i < n; i++)
                {
                    if (!parser(input))
                    {
                        std::cout << "sepBy: Parser not found\n";
                        return false;
                    }
                    std::cout << "sepBy: Current input after parser application: '" << input << "'\n";
                    if (!input.empty() && !separator(input))
                    {
                        std::cout << "sepBy: Separator not found\n";
                        return false;
                    }
                }
                bool consumed = original != input;
                std::cout << "sepBy: Consumed input? " << consumed << "\n";
                return consumed;
            };
        };

        /**
         * Parser that check if the `parser` is surrounded by the parsers `left` and `right`.
         *
         * @param left The parser to apply before `parser`.
         * @param parser The parser to apply.
         * @param right The parser to apply after `parser`.
         * @return A parser that check if the surrounding parsers `left` and `right` are applied.
         */
        auto surroundedBy = [](Parser left, Parser parser, Parser right) -> Parser
        {
            return [left, parser, right](std::string &input)
            {
                std::string original = input;
                if (!left(input))
                {
                    std::cout << "surroundedBy: Left parser not found\n";
                    return false;
                }
                std::cout << "surroundedBy: Current input after left parser application: '" << input << "'\n";
                if (!parser(input))
                {
                    std::cout << "surroundedBy: Parser not found\n";
                    return false;
                }
                std::cout << "surroundedBy: Current input after parser application: '" << input << "'\n";
                if (!right(input))
                {
                    std::cout << "surroundedBy: Right parser not found\n";
                    return false;
                }
                std::cout << "surroundedBy: Current input after right parser application: '" << input << "'\n";
                bool consumed = original != input;
                std::cout << "surroundedBy: Consumed input? " << consumed << "\n";
                return consumed;
            };
        };

    } // namespace c
} // namespace pc
