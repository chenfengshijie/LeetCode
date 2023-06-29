/*
 * @lc app=leetcode.cn id=115 lang=cpp
 *
 * [115] 不同的子序列
 */
#include <string>
#include <vector>
using std::string;
using std::vector;
// @lc code=start
class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.length(), m = t.length();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        s[0] == t[0] ? dp[0][0] = 1 : dp[0][0] = 0;
        for (int i = 1; i < n; i++)
            if (s[i] == t[0])
                dp[i][0] = dp[i - 1][0] + 1;
        for (int i = 1; i < n; i++)
            0 for (int j = 0; j < m && j <= i; j++)
            {
                if (s[i] == t[j])
                {
                    if (dp[i - 1][j] != 0)
                }
            }
    }
};
// @lc code=end
