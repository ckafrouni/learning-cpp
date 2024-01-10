#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#include "pc/pc.hpp"
#include "pc/parsers.hpp"
#include "pc/combinators.hpp"
#include "pc/utils.hpp"

#include "parsers/primitives.hpp"
#include "parsers/mov.hpp"

void runTest(pc::Parser parser, const std::vector<std::string> &validInputs,
             const std::vector<std::string> &invalidInputs, const std::string &testName)
{
        std::cout << "\033[1;33m## Running test: " << testName << "\033[0m" << std::endl;
        for (const auto &input : validInputs)
        {
                std::cout << "\033[1;34mShould succeed for input: " << input << "\033[0m" << std::endl;
                assert(parser(input.c_str()).success);
        }
        for (const auto &input : invalidInputs)
        {
                std::cout << "\033[1;35mShould fail for input: " << input << "\033[0m" << std::endl;
                assert(!parser(input.c_str()).success);
        }
        std::cout << "\033[1;32mTest passed: " << testName << "\033[0m" << std::endl;
}

int main()
{
        //     // Test for 'reg' parser
        //     runTest(reg,
        //             {"r1", "R4", "r2", "R3"}, // Valid inputs
        //             {"r5", "R0", "x1", "R"},  // Invalid inputs
        //             "reg");

        //     // Test for 'identifier' parser
        //     runTest(identifier,
        //             {"abc", "variable1", "x_123"}, // Valid inputs
        //             {"1abc", "!var", "*ident"},    // Invalid inputs
        //             "identifier");

        //     // Test for 'label_ref' parser
        //     runTest(label_def,
        //             {"label: ", "start: ", "end_label: "}, // Valid inputs
        //             {":label", "123label: ", "label"},     // Invalid inputs
        //             "label_def");

        //     // Test for 'label_ref' parser
        //     runTest(label_ref,
        //             {"!label", "!start_label "},      // Valid inputs
        //             {"label", "!123label", "_label"}, // Invalid inputs
        //             "label_ref");

        //     // Test for 'lit' parser
        //     runTest(lit,
        //             {"$0x1234 ", "$0x1ABC ", "$[0x123]"}, // Valid inputs
        //             {"1234", "0x1ABC", "$!expr"},         // Invalid inputs
        //             "lit");

        //     // Test for 'addr' parser
        //     runTest(addr,
        //             {"&r1 ", "&[0x1234] ", "&[!label]"}, // Valid inputs
        //             {"r1", "1234", "&x"},                // Invalid inputs
        //             "addr");

        //     // Test for 'op' parser
        //     runTest(op,
        //             {"+ ", "- ", "* ", "/ ", "% "}, // Valid inputs
        //             {"g", "$", "x", "&"},           // Invalid inputs
        //             "op");

        //     // Test for 'expr' parser
        //     runTest(expr,
        //             {"(0x32 + 0x32)", "(!label - 0x1234)", "!label"}, // Valid inputs
        //             {"(expr expr)", "label + $1234", "&(expr)"},      // Invalid inputs
        //             "expr");

        //     // // Test for 'sq_bracketed_expr' parser
        //     // runTest(sq_bracketed_expr,
        //     //         {"[expr]", "[label + expr]", "[&r1 - $0x1234]"}, // Valid inputs
        //     //         {"expr", "{expr}", "[label label]"},           // Invalid inputs
        //     //         "sq_bracketed_expr");

        //     // Test for 'src' parser
        //     runTest(src,
        //             {"r1", "&[!label]", "$0x1234"}, // Valid inputs
        //             {"label", "1234", "&"},         // Invalid inputs
        //             "src");

        //     // Test for 'dst' parser
        //     runTest(dst,
        //             {"r1", "&[!label]", "&[0x1234]"}, // Valid inputs
        //             {"$0x1234", "1234", "&"},      // Invalid inputs
        //             "dst");

        return 0;
}
