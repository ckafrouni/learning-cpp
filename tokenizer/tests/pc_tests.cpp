#include <string>
#include <iostream>

#include <cassert>

#include "pc/pc.hpp"
#include "pc/utils.hpp"

bool test_characters()
{
    std::cout << "Testing `ch(\"a\")`" << std::endl;

    auto c = pc::p::ch("a");

    for (auto i : {"a", "ab", "abc", "abcd", "abcde"})
    {
        auto result = c(i);
        assert(result.success);
    }

    // Should fail
    std::cout << "Testing `ch(\"b\")`" << std::endl;

    auto result = c("b");
    assert(!result.success);

    return true;
}

bool test_hexdigit()
{
    std::cout << "Testing `hex_digit`" << std::endl;

    for (auto i : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"})
    {
        auto result = pc::utils::hex_digit(i);
        assert(result.success);
    }

    assert(!pc::utils::hex_digit("g").success);

    return true;
}

bool test_digit()
{
    std::cout << "Testing `digit`" << std::endl;

    for (auto i : {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"})
    {
        auto result = pc::utils::digit(i);
        assert(result.success);
    }

    assert(!pc::utils::digit("a").success);

    return true;
}

int main()
{
    assert(test_characters());
    assert(test_hexdigit());
    assert(test_digit());

    return 0;
}
