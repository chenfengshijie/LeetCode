/*
 * @lc app=leetcode.cn id=132 lang=cpp
 *
 * [132] 分割回文串 II
 */
#include <string>
#include <vector>
using std::string;
using std::vector;
// @lc code=start
class Solution
{
public:
    int minCut(string s)
    {
        int n = s.length();
        vector<vector<bool>> g(n + 9, vector<bool>(n + 9, true));
        vector<int> f(n + 9, INT_MAX);
        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
            {
                g[i][j] = g[i + 1][j - 1] && s[i] == s[j];
            }
        for (int i = 0; i < n; i++)
        {
            if (g[0][i])
            {
                f[i] = 0;
                continue;
            }
            for (int j = i - 1; j >= 0; j--)
                if (g[j + 1][i])
                    f[i] = std::min(f[i], f[j] + 1);
        }
        return f[n - 1];
    }
};
// @lc code=end
