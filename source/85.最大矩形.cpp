/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */

#include <vector>
using std::vector;
// @lc code=start
class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int n = matrix.size();
        if (n == 0)
            return 0;
        int m = matrix[0].size();
        vector<int> num(n, 0);
        for (int i = 0; i < n; i++)
        {
            num.assign(n, 0);
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == '0')
                    continue;
                else
                    num[i] = num[i - 1] + 1;
            }
        }
    }
};
// @lc code=end
