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
} // namespace pc
