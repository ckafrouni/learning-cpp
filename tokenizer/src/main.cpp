#include <string>
#include <iostream>

#include "pc.hpp"
#include "parsers/mov.hpp"

int test_identifier()
{
    auto test_run_count = 0;
    auto test_success_count = 0;

    for (auto i : {"identifier", "snake_case", "camelCase", "PascalCase", "kebab-case", "UPPER_SNAKE_CASE"})
    {
        test_run_count++;
        std::string i2 = i;
        std::cout << "\033[1;33mParsing '" << i2 << "' using `identifier`\033[0m" << std::endl;
        if (identifier(i2))
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
    std::string i("1identifier");
    if (identifier(i))
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
        std::string i2 = i;
        std::cout << "\033[1;33mParsing '" << i2 << "' using `reg`\033[0m" << std::endl;
        if (reg(i2))
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
        std::string i2 = i;
        std::cout << "\033[1;33mParsing '" << i2 << "' using `hexDigit`\033[0m" << std::endl;
        if (hexDigit(i2))
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
        std::string i2 = i;
        std::cout << "\033[1;33mParsing '" << i2 << "' using `digit`\033[0m" << std::endl;
        if (digit(i2))
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

    for (auto i : {"labBel:", "Lab_el2:", "lab_el3_:", "lab\t:", "lab   :"})
    {
        test_run_count++;
        std::string i2 = i;
        std::cout << "\033[1;33mParsing '" << i2 << "' using `label`\033[0m" << std::endl;
        if (label_declaration(i2))
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        }
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
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
        std::string i2 = i;
        std::cout << "\033[1;33mParsing '" << i2 << "' using `label`\033[0m" << std::endl;
        if (label_reference(i2))
        {
            test_success_count++;
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
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
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }
    else
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;

    test_run_count++;
    if (test_hexdigit())
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }
    else
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;

    test_run_count++;
    if (test_register())
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }
    else
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;

    test_run_count++;
    if (test_identifier())
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }
    else
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;

    test_run_count++;
    if (test_label_decl())
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }
    else
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;

    test_run_count++;
    if (test_label_ref())
    {
        test_success_count++;
        std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
    }
    else
        std::cout << "\033[1;31mFailure!\033[0m" << std::endl;

    std::cout << "\033[1mRate: " << test_success_count << "/" << test_run_count << "\033[0m" << std::endl;

    auto str2 = [](std::string s) -> pc::ParserR
    {
        return [s](std::string str) -> pc::ParserResult
        {
            if (str.substr(0, s.length()) == s)
                return {true, 0, s.length(), str};
            else
                return {false, 0, 0, str};
        };
    };

    auto i = str2("hello");
    for (auto s : {"hello", "hello world", "hello world!"})
    {
        std::string s2 = s;
        auto r = i(s2);
        std::cout << "Parsing '" << s << "' using `str2(\"hello\")`" << std::endl;
        if (r.success)
            std::cout << "\033[1;32mSuccess!\033[0m" << std::endl;
        else
            std::cout << "\033[1;31mFailure!\033[0m" << std::endl;
        
        std::cout << "Result: \n\tSuccess: " << r.success << "\n\tStart: " << r.start << "\n\tEnd: " << r.end << std::endl;
    }


}
