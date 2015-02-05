//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

bool is_vowel(char c)
{
    switch ( c )
    {
    case 'I': case 'E': case 'A': case 'O': case 'U': case 'Y':
        return true;
    }
    return false;
}

double calc_harmonic(size_t n)
{
    static std::vector<double> harmonic_numbers;
    if (harmonic_numbers.empty())
    {
        harmonic_numbers.reserve(500001);
        harmonic_numbers.push_back(0);
        for (size_t i = 1; i <= 500000; ++i)
            harmonic_numbers.push_back(harmonic_numbers[i - 1] + 1.0 / double(i));
    }
    return harmonic_numbers[n];
}

double score(std::string const & title)
{
    size_t start = 0;
    double ret = 0, hn = 0;
    for (auto left = title.begin(), right = title.end() - 1; left <= right; ++left, -- right)
    {
        hn += calc_harmonic(title.size() - start) - calc_harmonic(start);
        start++;
        if (is_vowel(*left))
        {
            ret += hn;
        }

        if (right != left && is_vowel(*right))
        {
            ret += hn;
        }
    }

    return ret;
}



int main(int argc, char* argv[])
{
    std::string title;
    std::cin >> title;
    std::cout << std::fixed << std::setprecision(7) << score(title) << std::endl;

	return 0;
}
