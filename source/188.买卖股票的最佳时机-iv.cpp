/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;
// @lc code=start
class Solution
{
public:
    int f[1009][2][109];
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= k; j++)
                f[i][0][j] = f[i][1][j] = INT_MIN >> 1;
        f[0][0][0] = 0;
        f[0][1][1] = -prices[0];
        using std::max;
        for (int i = 1; i < n; i++)
        {
            f[i][0][0] = max(f[i][0][0], f[i - 1][0][0]);
            for (int j = 1; j <= k; j++)
            {
                f[i][0][j] = std::max(f[i][0][j], f[i - 1][0][j]);
                f[i][0][j] = max(f[i][0][j], f[i - 1][1][j] + prices[i]);
                f[i][1][j] = max(f[i][1][j], f[i - 1][1][j]);
                f[i][1][j] = max(f[i][1][j], f[i - 1][0][j - 1] - prices[i]);
            }
        }
        int ans = -1;
        for (int i = 0; i <= k; i++)
            ans = max(ans, f[n - 1][0][i]);
        return ans;
    }
};
Solution t;
// @lc code=end
int main()
{
    vector<int> c1{3, 2, 6, 5, 0, 3};
    auto ans = t.maxProfit(2, c1);
    printf("%d", ans);
    return 0;
}
