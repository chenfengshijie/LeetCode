/*
 * @lc app=leetcode.cn id=2572 lang=cpp
 *
 * [2572] 无平方子集计数
 */
#include <vector>
#include <algorithm>
using std::vector;
// @lc code=start
class Solution
{
public:
    int bitset[1009];
    int squareFreeSubsets(vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        nums.erase(std::unique(nums.begin(), nums.end()), nums.begin());
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 9 || nums[i] == 25 || nums[i] == 4 || nums[i] == 16)
            {
                std::swap(nums[i], nums.back());
                nums.pop_back();
            }
        }

        int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 11; j++)
                if (nums[i] % primes[j] == 0)
                    bitset[i] |= (1 << j);
        }
    }
};
// @lc code=end
