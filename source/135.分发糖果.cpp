/*
 * @lc app=leetcode.cn id=135 lang=cpp
 *
 * [135] 分发糖果
 */
#include <vector>
#include <algorithm>
#include <numeric>
using std::vector;
// @lc code=start
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int n = ratings.size();
        vector<int> f(n, 1);
        for (int i = 1; i < n; i++)
            if (ratings[i] > ratings[i - 1])
                f[i] = f[i - 1] + 1;
            else
                f[i] = 1;
        int count = 1;
        for (int i = n - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
                count += 1;
            else
                count = 1;
            f[i] = std::max(f[i], count);
        }
        return std::accumulate(f.begin(), f.end(), 0);
    }
};
// @lc code=end
int main()
{
    vector<int> c{1, 0, 2};
    Solution t;
    auto ans = t.candy(c);
    return 0;
}