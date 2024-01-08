#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

/*

<label declaration> ::=
    <label name> ':'

<label reference> ::=
    '!' <label name>

<mov> ::=
    "mov" <source> ',' <destination>


<source> ::=
    <register>
    | <address>
    | <immediate>

<destination> ::=
    <register>
    | <address>

<address> ::=
    '&' <register>
    | '&' <immediate>

<register> ::=
    r1 | r2 | r3 | r4

<immediate> ::=
    '$' <number>
    | '$' <label reference>

<number> ::=
    <hexadecimal>
    | <decimal>

<hexadecimal> ::=
    '0x' <hexadecimal digit>+

<decimal> ::=
    <decimal digit>+

<hexadecimal digit> ::=
    '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
    | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'

<decimal digit> ::=
    '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'
    | '8' | '9'



    




*/

enum class TokenType
{
    Register,
    Address,
    Immediate,
    LabelDeclaration,
    LabelReference,
    Comment,
    Instruction,
    Punctuation,
    Unknown
};

static constexpr const char *TokenTypeStrings[] = {
    "Register",
    "Address",
    "Immediate",
    "Label",
    "Comment",
    "Instruction",
    "Punctuation",
    "Unknown"};

struct Token
{
    TokenType type;
    std::string value;
    // int line;
    // int column;
};

std::ostream &operator<<(std::ostream &os, const TokenType &type)
{
    os << TokenTypeStrings[static_cast<int>(type)];
    return os;
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << "Token{ ";
    if (token.type == TokenType::Unknown)
    {
        os << "\033[31m"
           << token.type
           << "\033[0m, ";
    }
    else
    {
        os << token.type << ", ";
    }
    os << "`"
       << "\033[32m" << token.value << "\033[0m" << '`' << " }";

    return os;
}

TokenType determineTokenType(const std::string &token)
{
    if (token[0] == 'r')
    {
        return TokenType::Register;
    }
    else if (token[0] == '&')
    {
        return TokenType::Address;
    }
    else if (token[0] == '$')
    {
        return TokenType::Immediate;
    }
    else if (token.rfind("//", 0) == 0)
    { // starts with "//"
        return TokenType::Comment;
    }
    else if (std::regex_match(token, std::regex("mov|jmp")))
    {
        return TokenType::Instruction;
    }
    else if (token.back() == ':')
    {
        return TokenType::LabelDeclaration;
    }
    else if (token.front() == '!')
    {
        return TokenType::LabelReference;
    }
    else if (std::regex_match(token, std::regex("[,;]")))
    {
        return TokenType::Punctuation;
    }
    else
    {
        return TokenType::Unknown;
    }
}

std::vector<Token> tokenize(const std::string &line)
{
    std::vector<Token> tokens;

    std::regex regex(R"(\S+)");
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::string tokenValue = (*i).str();
        TokenType type = determineTokenType(tokenValue);

        // If it's a comment, add it and consume the rest of the line as the comment
        if (type == TokenType::Comment)
        {
            tokens.push_back(Token{type, line.substr(i->position())});
            break;
        }

        tokens.push_back(Token{type, tokenValue});
    }

    return tokens;
}

std::vector<std::vector<Token>> processInput(const std::string &input)
{
    std::istringstream stream(input);
    std::vector<std::vector<Token>> tokenLines;
    std::string line;

    while (std::getline(stream, line))
    {
        tokenLines.push_back(tokenize(line));
    }

    return tokenLines;
}

int main()
{
    std::string input = "main:\n"
                        "                 mov $0x12, r1              // This is a comment\n"
                        "                 mov r1, &r2\n"
                        "                 jmp !main\n";

    auto tokenLines = processInput(input);

    // Output tokens for demonstration
    for (const auto &line : tokenLines)
    {
        for (const auto &token : line)
        {
            std::cout << token << std::endl;
        }
    }

    return 0;
}
