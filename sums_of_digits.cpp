//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

std::string get_min_a(int b)
{
    auto count = b / 9;
    auto first = b % 9;
    std::string ret;
    if (first) ret += '0' + first;
    ret += std::string(count, '9');
    return ret;
}

void align_digits(std::string & a, size_t digits)
{
    if (digits == a.size()) return;
    --a[0];
    a = '1' + std::string(digits - a.size() - 1, '0') + a;
}

bool greater (std::string const & l, std::string const & r)
{
    if (l.size() > r.size()) return true;
    if (l.size() < r.size()) return false;
    for (auto it_l = l.begin(), it_r = r.begin(); it_l != l.end(); ++it_l, ++it_r)
    {
        if (*it_l > *it_r) return true;
        if (*it_l < *it_r) return false;
    }
    return false;
}

void align_front(std::string & a, std::string const & prev)
{
    auto it_a = a.begin(), supply = std::find_if(a.begin() + 1, a.end(), [](char chr){return chr != '0';});
    auto it_p = prev.begin();
    // make as many digits as possible equal in a to prev starting from the left
    while (supply < a.end())
    {
        auto space = *it_p - *it_a;
        if (space < 0) break;
        auto value = *supply - '0';
        auto diff = space < value ? space : value;
        *it_a += diff;
        *supply -= diff;
        if (*it_a == *it_p)
        {
            ++it_a; ++it_p;
        }
        if (supply == it_a || *supply == '0') ++supply;
    }
}

std::string get_a(int b, std::string const & prev)
{
    // get the minimum possible a
    auto a = get_min_a(b);
    if (greater(a, prev)) return a;
    // get the minimum possible a that has the same number of digits as prev
    align_digits(a, prev.size());
    if (greater(a, prev)) return a;
    // a has following format {10..0}#{9..9}
    align_front(a, prev);
    if (greater(a, prev)) return a;
    // now a has following format {prev_prefix}#{0..0} (and is smaller than prev)
    // so find the first non zero digit from the end
    auto digit = std::find_if(a.rbegin(), a.rend(), [](char chr){return chr != '0';});
    // decrement it
    --(*digit);
    // than look for the next one that is smaller than '9'
    digit = std::find_if(digit + 1, a.rend(), [](char chr){return chr != '9';});
    // and increment the digit
    if (digit == a.rend())
    {
        a = '1' + a;
        digit = a.rend() - 1;
    }
    else
        ++(*digit);
    // than move every thing right to the incremented digit as far to the right as possible
    auto it = digit.base(), store = a.end() - 1;
    while (it < store)
    {
        auto space = '9' - *store;
        auto value = *it - '0';
        auto diff = space < value ? space : value;
        *store += diff;
        *it -= diff;
        if (*store == '9') --store;
        if (*it == '0') ++it;
    }
    // and return a
    return a;
}

int main(int argc, char* argv[])
{
    size_t count = 0;
    std::cin >> count;

    int b = 0;
    std::string prev;
    for (size_t i = 0; i < count; ++i)
    {
        std::cin >> b;
        std::cout << (prev = get_a(b, prev)) << std::endl;;
    }

	return 0;
}
