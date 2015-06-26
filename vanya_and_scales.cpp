//============================================================================
// Name        : test.cpp
// Author      : Michal Simon
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include <math.h>

bool solve(long long base, long long m, std::vector<bool> & mem)
{
    if (m == 0) return true;

    long long ex1 = log(m) / log(base), ex2 = ex1 + 1;
    long long w1 = pow(base, ex1);
    long long w2 = pow(base, ex2);
    bool ret1 = false, ret2 = false;

    if (ex1 <= 100 && mem[ex1])
    {
        mem[ex1] = false;
        ret1 = solve(base, m - w1, mem);
        mem[ex1] = true;
    }

    if (ex2 <= 100 && mem[ex2])
    {
        mem[ex2] = false;
        ret2 = solve(base, w2 - m, mem);
        mem[ex2] = true;
    }

    return ret1 || ret2;
}

int main()
{
    long long w, m;
    std::cin >> w;
    std::cin >> m;

    std::vector<bool> mem (101, true);

    if (solve(w, m, mem))
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO"  << std::endl;

    return 0;
}
