/*
 * @lc app=leetcode.cn id=164 lang=cpp
 *
 * [164] 最大间距
 */
#include <vector>
#include <algorithm>
using std::vector;
// @lc code=start
class Solution
{
public:
    int maximumGap(vector<int> &nums)
    {
        int max_num = *std::max_element(nums.begin(), nums.end());
        int min_num = *std::min_element(nums.begin(), nums.end());
        int n = nums.size();
        int interval = (max_num - min_num) / n;
    }
};
// @lc code=end
