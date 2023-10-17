/*
 * @lc app=leetcode.cn id=87 lang=cpp
 *
 * [87] 扰乱字符串
 */
#include <string>
#include <array>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution
{
public:
    int f[50][50][50];
    bool isScramble(string s1, string s2)
    {
        memset(f, 0, sizeof(f));
        int n = s1.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (s1[i] == s2[j])
                    f[i][j][1] = 1;
        for (int len = 2; len <= n; len++)
            for (int i = 0; i <= n - len; i++)
                for (int j = 0; j <= n - len; j++)
                    for (int k = 1; k < len; k++)
                    {
                        if (f[i][j][k] && f[i + k][j + k][len - k])
                        {
                            f[i][j][len] = 1;
                            break;
                        }
                        if (f[i][j + len - k][k] && f[i + k][j][len - k])
                        {
                            f[i][j][len] = 1;
                            break;
                        }
                    }
        return f[0][0][n];
    }
};
// @lc code=end
