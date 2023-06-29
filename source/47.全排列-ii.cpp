/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */
#include <vector>
#include <algorithm>
using std::vector;
// @lc code=start
class Solution
{
public:
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<vector<int>> ret;
        std::sort(begin(nums), end(nums));
        do
        {
            ret.emplace_back(nums);
        } while (next_permutation(begin(nums), end(nums)));
        return ret;
    }
};
// @lc code=end
