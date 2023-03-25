/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */
#include <vector>
#include <algorithm>
using std::vector;
// @lc code=start
class Solution
{
public:
    int f[300009][2][3];
    int maxProfit(vector<int> &prices)
    {

        int n = prices.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 3; j++)
            {
                f[i][0][j] = f[i][1][j] = INT_MIN >> 1;
            }
        f[0][0][0] = 0;
        f[0][1][1] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                switch (j)
                {
                case 0:
                    f[i][0][j] = std::max(f[i][0][j], f[i - 1][0][j]);
                    break;
                case 1:
                case 2:
                    f[i][0][j] = std::max(f[i][0][j], f[i - 1][0][j]);
                    f[i][0][j] = std::max(f[i][0][j], f[i - 1][1][j] + prices[i]);
                    f[i][1][j] = std::max(f[i][1][j], f[i - 1][1][j]);
                    f[i][1][j] = std::max(f[i][1][j], f[i - 1][0][j - 1] - prices[i]);
                    break;
                default:
                    break;
                }
            }
        }
        return std::max(f[n - 1][0][0], std::max(f[n - 1][0][1], f[n - 1][0][2]));
    }
};
// @lc code=end
Solution t;
int main()
{
    vector<int> c1{7, 6, 5, 4, 3, 2, 1};
    auto ans = t.maxProfit(c1);
    printf("%d", ans);
    return 0;
}