#pragma once


#include <ctre.hpp>
#include <vector>
#include <string>

struct Token {
    const char *token_type;
    const char *value;
};

// Define regular expressions for each token type
constexpr auto label_declaration = ctll::fixed_string{R"((r[1-4]):)"};
constexpr auto label_reference = ctll::fixed_string{R"(!r[1-4])"};
constexpr auto mov_instruction = ctll::fixed_string{R"(mov\s+([^,]+),\s*(.+))"};
constexpr auto register_regex = ctll::fixed_string{R"(r[1-4])"};
constexpr auto immediate = ctll::fixed_string{R"(\$0x[0-9a-f]+|\$\d+|\$!r[1-4])"};
constexpr auto address = ctll::fixed_string{R"(&r[1-4]|&\$0x[0-9a-f]+|&\$\d+|&\$!r[1-4])"};


std::vector<Token> lexer(const std::string& input) {
    std::vector<Token> tokens;

    // Tokenize the input using CTRE
    for (auto it = input.begin(); it != input.end(); ++it) {
        // Match each token type
        if (auto [whole, label_name] = ctre::match<label_declaration>(it, input.end()); label_name) {
            tokens.push_back({"Label Declaration", label_name.to_string().c_str()});
            it += whole.size() - 1;  // Advance iterator
        } else if (auto [whole, label_ref] = ctre::match<label_reference>(it, input.end()); label_ref) {
            tokens.push_back({"Label Reference", label_ref.to_string().c_str()});
            it += whole.size() - 1;
        } else if (auto [whole, source, destination] = ctre::match<mov_instruction>(it, input.end()); source && destination) {
            tokens.push_back({"MOV Instruction", whole.to_string().c_str()});
            it += whole.size() - 1;
        } // ... Additional token types ...
    }

    return tokens;
}


int main() {
    std::string input = "mov r1, r2\nr3: mov $0x10, &r4\n!r3";

    auto tokens = lexer(input);

    // Output tokens
    for (const auto& token : tokens) {
        std::cout << "Token Type: " << token.token_type << ", Value: " << token.value << std::endl;
    }

    return 0;
}

