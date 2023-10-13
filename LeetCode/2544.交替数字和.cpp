/*
 * @lc app=leetcode.cn id=2544 lang=cpp
 *
 * [2544] 交替数字和
 */

// @lc code=start
class Solution
{
public:
    int alternateDigitSum(int n)
    {
        int ans = 0;
        int flag = 1;
        while (n != 0)
        {
            ans += flag * (n % 10);
            flag *= -1;
            n /= 10;
        }
        return ans * -flag;
    }
};
// @lc code=end
