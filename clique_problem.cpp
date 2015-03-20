#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct solution
{
    solution(std::vector<std::pair<int, int>> const & input)
    {
        // transform input into {sum, diff} pairs
        std::transform(input.begin(), input.end(), std::back_inserter(sum_diff), [](std::pair<int, int> const & p){return std::make_pair(p.first + p.second, p.first - p.second);});
        // sort in ascending order first by sum, than by difference
        std::sort(sum_diff.begin(), sum_diff.end());
        // remove duplicate entries with the same sum (keep the one with maximum difference)
        auto it = sum_diff.begin(), store = sum_diff.begin();
        while(it != sum_diff.end())
        {
            *store = *it;
            ++it;
            if(it != sum_diff.end() && it->first != store->first)
                ++store;
        }
        // shrink the vector if necessary
        sum_diff.resize(std::distance(sum_diff.begin(), it));
    }

    int solve()
    {
        // the first item is the first vertex in the clique
        auto it = sum_diff.begin(), vertex = sum_diff.begin();
        // count the first vertex
        auto count = 1;
        while(it != sum_diff.end())
        {
            // xi - wi >= xj + wj
            if (it->second >= vertex->first)
            {
                // next vertex has been found
                vertex = it;
                ++count;
            }
            ++it;
        }
        return count;
    }

private:
    std::vector<std::pair<int, int>> sum_diff;
};

int main(int argc, char* argv[])
{
    std::vector<std::pair<int, int>> input;
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int x, w;
        std::cin >> x >> w;
        input.push_back({x, w});
    }

    solution s(input);
    std::cout << s.solve() << std::endl;

    return 0;
}
