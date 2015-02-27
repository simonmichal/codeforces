//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <tuple>
#include <queue>
#include <map>

int gcd(int a, int b)
{
    while (b != 0)
    {
        auto tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}

int set_gcd(std::set<int> const & s)
{
    auto ret = 0;
    for(auto number : s)
        ret = gcd (ret, number);
    return ret;
}

typedef std::tuple<int, int, std::set<int>> solution;
typedef std::priority_queue<solution, std::vector<solution>, std::greater<solution>> min_heap;

int solve(std::map<int, int> const & cards_costs)
{
    min_heap heap;
    std::set<int> card_set;
    int cost, gcd;
    heap.push(solution());
    std::map<int, int> memo;

    while(!heap.empty())
    {
        std::tie(cost, gcd, card_set) = heap.top(); heap.pop();
        // base case
        if (gcd == 1) return cost;
        // look for the result
        for (auto card_cost : cards_costs)
        {
            if (!card_set.count(card_cost.first))
            {
                auto s = card_set;
                s.insert(card_cost.first);
                auto c = cost + card_cost.second;
                gcd = set_gcd(s);
                if (memo.find(gcd) == memo.end() || memo[gcd] > c)
                {
                    memo[gcd] = c;
                    heap.push(solution(c, gcd, s));
                }
            }
        }
    }

    return -1;
}

int main(int argc, char* argv[])
{
    std::map<int, int> cards_costs;
    std::vector<int> cards, costs;
    auto size = 0;
    std::cin >> size;
    for (int i = 0; i < size; ++i)
    {
        int tmp;
        std::cin >> tmp;
        cards.push_back(tmp);
    }
    for (int i = 0; i < size; ++i)
    {
        int tmp;
        std::cin >> tmp;
        costs.push_back(tmp);
    }
    for (size_t i = 0; i < cards.size(); ++i)
        if (cards_costs.find(cards[i]) == cards_costs.end() || cards_costs[cards[i]] > costs[i])
            cards_costs[cards[i]] = costs[i];
    std::cout << solve(cards_costs) << std::endl;

    return 0;
}
