#include <string>
#include <iostream>

#include "pc/pc.hpp"
#include "pc/utils.hpp"

#include "parsers/mov.hpp"

int test_characters()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    auto c = pc::p::ch("a");

    for (auto i : {"a", "ab", "abc", "abcd", "abcde"})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `ch(\"a\")`\033[0m" << std::endl;
        auto result = c(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    // Should fail
    test_run_count++;
    auto result = c("b");
    if (result.success)
    {
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }
    else
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_identifier()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"identifier", "snake_case", "camelCase", "PascalCase", "kebab-case", "UPPER_SNAKE_CASE"})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `identifier`\033[0m" << std::endl;
        auto result = identifier(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    // Should fail
    std::cout << "\033[1;33mParsing '1identifier' using `identifier`\033[0m" << std::endl;
    test_run_count++;
    auto i("1identifier");
    auto result = identifier(i);
    if (result.success)
        std::cout
            << "\033[1;31mFailure!\033[0m" << std::endl;
    else
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_register()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"r1", "r2", "r3", "r4"})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `reg`\033[0m" << std::endl;
        auto result = reg(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_hexdigit()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `hexDigit`\033[0m" << std::endl;
        auto result = pc::utils::hexDigit(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_digit()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `digit`\033[0m" << std::endl;
        auto result = pc::utils::digit(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_label_decl()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"labBel:", "Lab_el2:", "lab_el3_:", "lab\t:", "lab   :      k"})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `label`\033[0m" << std::endl;
        auto result = label_declaration(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
            std::cout << "\033[1;34m-> Start: " << result.start << "\n-> End: " << result.end << "\n-> Parsed: [ ";
            for (const auto &parsed : result.parsed)
            {
                std::cout << "'" << parsed << "', ";
            }
            std::cout << "]\n-> Remaining: '" << result.remaining << "'\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    // should fail
    test_run_count++;
    auto i = "nocolon";
    std::cout << "\033[1;33mParsing '" << i << "' using `label`\033[0m" << std::endl;
    auto result = label_declaration(i);
    if (result.success)
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    else
    {
        test_success_count++;
        std::cout << "\033[1;32mCorrectly Failed!\033[0m" << std::endl;
        std::cout << "\033[1;34m-> Start: " << result.start << "\n-> End: " << result.end << "\n-> Parsed: [ ";
        for (const auto &parsed : result.parsed)
        {
            std::cout << "'" << parsed << "', ";
        }
        std::cout << "]\n-> Remaining: '" << result.remaining << "'\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_label_ref()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"!labBel", "!Lab_el2", "!lab_el3_", "!lab\t", "!lab   "})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `label`\033[0m" << std::endl;
        auto result = label_reference(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int test_mov_reg_reg()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"mov r1, r2", "mov r3,r4", "mov r1 , r4", "mov r2, r3   "})
    {
        test_run_count++;
        std::cout << "\033[1;33mParsing '" << i << "' using `mov`\033[0m" << std::endl;
        auto result = mov_reg_reg(i);
        if (result.success)
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
            std::cout << "\033[1;34m-> Start: " << result.start << "\n-> End: " << result.end << "\n-> Parsed: [ ";
            for (const auto &parsed : result.parsed)
            {
                std::cout << "'" << parsed << "', ";
            }
            std::cout << "]\n-> Remaining: '" << result.remaining << "'\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
    }

    return test_success_count == test_run_count;
}

int main()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    test_run_count++;
    if (test_digit())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_hexdigit())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_register())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_identifier())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_characters())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_label_decl())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_label_ref())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    test_run_count++;
    if (test_mov_reg_reg())
    {
        test_success_count++;
        std::cout << "\033[1;32m-> Success!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m-> Failure!\033[0m" << std::endl;
    }

    std::cout << std::endl;

    std::cout << "\033[1;34m=> Rate: " << test_success_count << "/" << test_run_count << "\033[0m" << std::endl;
}
