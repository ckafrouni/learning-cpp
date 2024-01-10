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

    class Parser
    {
    public:
        std::function<ParserResult(const char *)> parseFunction;
        std::string name;

        Parser(std::function<ParserResult(const char *)> func, const std::string &n = "")
            : parseFunction(std::move(func)), name(n) {}

        ParserResult parse(const char *input) const
        {
            return parseFunction(input);
        }

        // Callable operator for convenience
        ParserResult operator()(const char *input) const
        {
            return parse(input);
        }
    };

    // /**
    //  * Type for the parser function that returns a `ParserResult`.
    //  *
    //  * @param str The string to parse.
    //  * @return The result of the parser.
    //  */
    // using Parser = std::function<ParserResult(const char *)>;

} // namespace pc
