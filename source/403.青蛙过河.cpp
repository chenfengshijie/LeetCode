/*
 * @lc app=leetcode.cn id=403 lang=cpp
 *
 * [403] 青蛙过河
 */
#include <vector>
using std::vector;
// @lc code=start
class Solution
{
public:
    bool canCross(vector<int> &stones)
    {
        int n = stones.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        dp[0][1] = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                dp[i][j] = (dp[i - j][j] | dp[i][j - 1] | dp[i - j][j + 1]);
            }
        }
        bool ans;
        for (int i = 0; i < n; i++)
            ans |= dp[n - 1][i];
        return ans;
    }
};
// @lc code=end
Solution t;
int main()
{
    vector<int> c1{0, 1, 2, 3, 4, 8, 9, 11};
    auto ans = t.canCross(c1);

    return 0;
}
