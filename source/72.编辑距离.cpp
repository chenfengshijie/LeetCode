/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

#include <string>
using std::string;
// @lc code=start
class Solution
{
public:
    int f[509][509];
    int minDistance(string word1, string word2)
    {
        memset(f, 0x123, sizeof(f));
        f[0][0] = 0;
        int n = word1.length(), m = word2.length();
        for (int i = 1; i <= n; i++)
        {
            f[i][0] = i;
        }
        for (int i = 1; i <= m; i++)
            f[0][i] = i;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (word1[i - 1] == word2[j - 1])
                    f[i][j] = f[i - 1][j - 1];
                else
                    f[i][j] = std::min(f[i - 1][j - 1], std::min(f[i - 1][j], f[i][j - 1])) + 1;
        return f[n][m];
    }
};
// @lc code=end

int main()
{
    Solution t;
    string word1 = "horse";
    string word2 = "ros";
    printf("--------%d\n------", t.minDistance(word1, word2));
    return 0;
}