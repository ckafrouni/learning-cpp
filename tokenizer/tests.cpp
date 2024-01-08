#include <string>
#include <functional>
#include <iostream>
#include <tuple>

// Define the type for the parser function
using Parser = std::function<bool(std::string &)>;

// Flow control combinators
auto choiceParser = [](Parser parser1, Parser parser2) -> Parser
{
    return [parser1, parser2](std::string &input)
    {
        std::cout << "choiceParser: Trying first parser on input '" << input << "'\n";
        bool result = parser1(input);
        if (!result)
        {
            std::cout << "choiceParser: Trying second parser on input '" << input << "'\n";
            result = parser2(input);
        }
        return result;
    };
};

template <typename... Parsers>
auto chainParser(Parsers... parsers) -> Parser
{
    return [parsers = std::make_tuple(parsers...)](std::string &input) mutable
    {
        return std::apply([&](auto &...args)
                          { return (... && (std::cout << "chainParser: Applying parser on input '" << input << "'\n", args(input))); },
                          parsers);
    };
}

auto oneOrMore = [](Parser parser) -> Parser
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

auto zeroOrMore = [](Parser parser) -> Parser
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

// Basic parsers
auto charParser = [](char c) -> Parser
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

auto stringParser = [](const std::string &s) -> Parser
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

auto digitParser = [](std::string &input)
{
    if (!input.empty() && isdigit(input[0]))
    {
        std::cout << "digitParser: Consuming '" << input[0] << "'\n";
        input.erase(0, 1);
        return true;
    }
    std::cout << "digitParser: Not a digit '" << input << "'\n";
    return false;
};

auto comaSeparated = [](Parser parser) -> Parser
{
    return [parser](std::string &input)
    {
        std::string original = input;
        while (!input.empty() && parser(input))
        {
            std::cout << "comaSeparated: Current input after parser application: '" << input << "'\n";
            if (!input.empty() && input[0] == ',')
            {
                std::cout << "comaSeparated: Consuming ','\n";
                input.erase(0, 1);
            }
        }
        bool consumed = original != input;
        std::cout << "comaSeparated: Consumed input? " << consumed << "\n";
        return consumed;
    };
};

int main()
{
    std::string input = "mov r1, r2";

    auto reg = chainParser(
        charParser('r'),
        digitParser);

    auto zeroOrMoreSpaces = zeroOrMore(charParser(' '));
    auto oneOrMoreSpaces = oneOrMore(charParser(' '));

    // auto parser_mov = chainParser(
    //     stringParser("mov"),
    //     oneOrMoreSpaces,
    //     reg,
    //     zeroOrMoreSpaces,
    //     charParser(','),
    //     zeroOrMoreSpaces,
    //     reg,
    //     zeroOrMoreSpaces);

    auto parser_mov = chainParser(
        stringParser("mov"),
        oneOrMoreSpaces,
        comaSeparated(reg),
        zeroOrMoreSpaces);

    std::cout << "Parsing '" << input << "' with parser_mov" << std::endl;
    bool result = parser_mov(input);
    std::cout << "Result: " << result << std::endl;
    std::cout << "Remaining input: '" << input << "'\n";
}
