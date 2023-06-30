/*
 * @lc app=leetcode.cn id=137 lang=cpp
 *
 * [137] 只出现一次的数字 II
 */
#include <vector>
#include <bitset>
#include <algorithm>
#include <iostream>
using std::vector;
// @lc code=start
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        vector<int> bits(32, 0);
        int n = nums.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 32; j++)
                if (nums[i] & (1 << j))
                    bits[j]++;

        auto lmd = [](int &a)
        { a = a % 3; };
        std::for_each(bits.begin(), bits.end(), lmd);
        int ans = 0;
        for (int j = 0; j < 32; j++)
            if (bits[j])
                ans |= (1 << j);
        return ans;
    }
};
// @lc code=end
int main()
{
    std::ios::sync_with_stdio(false);
    vector<int> c{30000, 500, 100, 30000, 100, 30000, 100};
    Solution t;
    auto ans = t.singleNumber(c);
    std::cout << ans;
    return 0;
}
