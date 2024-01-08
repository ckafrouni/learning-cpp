#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <tuple>
#include <regex>

namespace pc
{
    // Define the type for the parser function
    using Parser = std::function<bool(std::string &)>;

    // Define the result structure that we will use to return the result of the parser function other than a boolean
    struct ParserResult
    {
        bool success;
        unsigned long start;
        unsigned long end;
        std::string value;
    };

    // Define the type for the new parser function that returns a Result
    using ParserR = std::function<ParserResult(std::string &)>;

    namespace p
    {
        /**
         * Parser that matches the character `c`.
         *
         * @param c The character to match.
         * @return A parser that matches the character `c`.
         */
        auto ch = [](char c) -> Parser
        {
            return [c](std::string &input)
            {
                if (!input.empty() && input[0] == c)
                {
                    std::cout << "charParser('" << c << "'): Consuming '" << input[0] << "'\n";
                    input.erase(0, 1);
                    return true;
                }
                std::cout << "charParser('" << c << "'): Not matching '" << input << "'\n";
                return false;
            };
        };

        /**
         * Parser that matches the string `s`.
         *
         * @param s The string to match.
         * @return A parser that matches the string `s`.
         */
        auto str = [](const std::string &s) -> Parser
        {
            return [s](std::string &input)
            {
                if (input.substr(0, s.size()) == s)
                {
                    std::cout << "stringParser('" << s << "'): Consuming '" << input.substr(0, s.size()) << "'\n";
                    input.erase(0, s.size());
                    return true;
                }
                std::cout << "stringParser('" << s << "'): Not matching '" << input << "'\n";
                return false;
            };
        };

        /**
         * Parser that matches the regular expression `s`.
         *
         * @param s The regular expression to match.
         * @return A parser that matches the regular expression `s`.
         */
        auto regex = [](const std::string &s) -> Parser
        {
            return [s](std::string &input)
            {
                std::regex r(s);
                std::smatch m;
                if (std::regex_search(input, m, r))
                {
                    std::cout << "regexParser('" << s << "'): Consuming '" << m[0] << "'\n";
                    input.erase(0, m[0].length());
                    return true;
                }
                std::cout << "regexParser('" << s << "'): Not matching '" << input << "'\n";
                return false;
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

        /**
         * Parser that applies the parsers `parsers` in order.
         *
         * @param parsers The parsers to apply in order.
         * @return A parser that applies the parsers `parsers` in order.
         */
        template <typename... Parsers>
        auto chain(Parsers... parsers) -> Parser
        {
            return [parsers = std::make_tuple(parsers...)](std::string &input) mutable
            {
                return std::apply([&](auto &...args)
                                  { return (... && (std::cout << "chainParser: Applying parser on input '" << input << "'\n", args(input))); },
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
