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
        auto chain(Parsers... parsers) -> pc::Parser
        {
            static int i = 0;
            return pc::Parser([parsers = std::make_tuple(parsers...)](const char *input) mutable
                              {
                            
            int j = 0;
                std::cout << "<chain #" << ++i <<"> Trying chain on input : '" << input << "'" << std::endl;
                size_t start = 0;
                std::vector<std::string> value;
                std::string remaining = input;

                return std::apply([&](auto &...args)
                                  {
                    bool success = (... && [&](auto &parser) {
                        std::cout << "  <chain #" << i << "."<< ++j <<"> testing : '" << parser.name << "' on input : '" << remaining << "'" << std::endl;
                        pc::ParserResult result = parser(remaining.c_str());
                        if (result.success) {
                            start = (start == 0) ? result.start : start;
                            value.insert(value.end(), result.parsed.begin(), result.parsed.end());
                            remaining = result.remaining;
                            return true;
                        }
                        else {
                            std::cout << "  <chain> Failed to parse with parser : '" << parser.name <<"' on input : '" << remaining << "'" << std::endl;

                            return false;
                        }
                    }(args));
                    
                    size_t end = start + value.size();
                    return pc::ParserResult{success, start, end, value, remaining}; },
                                  parsers); },
                              "chain");
        }

        template <typename... Parsers>
        auto choice(Parsers... parsers) -> pc::Parser
        {
            static int i = 0;
            return pc::Parser([parsers = std::make_tuple(parsers...)](const char *input) mutable
                              {
                                            int j = 0;

                                std::cout << "<choice #"<< ++i<<"> Trying choice on input : '" << input << "'" << std::endl;
                pc::ParserResult result;
                std::apply([&](auto &...args)
                           { (... || [&](auto &parser)
                              {
                                   std::cout << "  <choice #" << i << "." << ++j << "> testing : '" << parser.name << "' on input : '" << input << "'" << std::endl;
                                   result = parser(input);
                                   return result.success; }(args)); },
                           parsers);
                return result; },
                              "choice of " + std::to_string(sizeof...(parsers)) + " parsers");
        }

        /**
         * Parser that doesn't collect the result of the parser `parser`.
         *
         * @param parser The parser to skip.
         * @return A parser that skips the parser `parser`.
         */
        auto skip = [](pc::Parser parser) -> pc::Parser
        {
            return pc::Parser(
                [parser](const char *input) -> pc::ParserResult
                {
                    pc::ParserResult result = parser.parse(input);
                    if (result.success)
                    {
                        // Clear parsed output, keep success status and remaining string
                        result.parsed.clear();
                    }
                    return result;
                },
                "skip(" + parser.name + ")");
        };

        /**
         * Parser that succeeds even if the parser `parser` fails.
         *
         * @param parser The parser to try.
         * @return A parser that tries the parser `parser`.
         */
        auto optional = [](pc::Parser parser) -> pc::Parser
        {
            return pc::Parser([parser](const char *input) -> pc::ParserResult
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
                return result; },
                              "optional(" + parser.name + ")");
        };

        /**
         * Parser that succeed if `parser` is surrounded by `left` and `right`.
         *
         * @param left The left parser.
         * @param parser The parser to surround.
         * @param right The right parser.
         * @return A parser that surrounds `parser` with `left` and `right`.
         */
        auto surround = [](pc::Parser left, pc::Parser parser, pc::Parser right) -> pc::Parser
        {
            return pc::Parser([left, parser, right](const char *input) -> pc::ParserResult
                              {
                std::cout << "Trying surround with : '" << left.name << "' on input : '" << input << "'" << std::endl;
                pc::ParserResult result = left(input);
                std::cout << "Parser result : " << result.success << std::endl;
                if (result.success)
                {
                    std::cout << "Trying parser : '" << parser.name << "' on input : '" << result.remaining << "'" << std::endl;
                    pc::ParserResult result2 = parser(result.remaining.c_str());
                    if (result2.success)
                    {
                        std::cout << "Trying parser : '" << right.name << "' on input : '" << result2.remaining << "'" << std::endl;
                        pc::ParserResult result3 = right(result2.remaining.c_str());
                        if (result3.success)
                        {
                            result.end = result3.end;
                            result.parsed.insert(result.parsed.end(), result2.parsed.begin(), result2.parsed.end());
                            result.remaining = result3.remaining;
                        }
                        else
                        {
                            result.success = false;
                        }
                    }
                    else
                    {
                        result.success = false;
                    }
                }
                return result; },
                              "surround(" + left.name + ", " + parser.name + ", " + right.name + ")");
        };
    } // namespace c
} // namespace pc
