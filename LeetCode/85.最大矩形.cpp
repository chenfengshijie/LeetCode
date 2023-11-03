/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
// @lc code=start
class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int sum[209][209];
        memset(sum, 0, sizeof(sum));
        int n = matrix.size(), m = matrix[0].size();
        for (int row = 0; row < n; row++)
            if (matrix[row][0] == '1')
                sum[row][0] = 1;
        for (int row = 0; row < n; row++)
            for (int col = 1; col < m; col++)
                if (matrix[row][col] == '1')
                    sum[row][col] = 1 + sum[row][col - 1];
        int ans = 0;
        stack<int> left;

        for (int col = 0; col < m; col++)
        {
            vector<int> max_left(209, 0), max_right(209, n);
            while (!left.empty())
                left.pop();
            sum[n + 1][col] = -1;
            for (int row = 0; row <= n; row++)
            {
                while (!left.empty() && sum[left.top()][col] > sum[row][col])
                {
                    max_right[left.top()] = row;
                    left.pop();
                }
                max_left[row] = left.empty() ? -1 : left.top();
                left.push(row);
            }
            for (int row = 0; row < n; row++)
                ans = max<int>(ans, (max_right[row] - max_left[row] - 1) * sum[row][col]);
        }
        return ans;
    }
};
// @lc code=end
int main()
{
    vector<vector<char>> maxtrix = {{'1', '1'}};
    // {
    // {'1', '0', '1', '0', '0'},
    // {'1', '0', '1', '1', '1'},
    // {'1', '1', '1', '1', '1'},
    // {'1', '0', '0', '1', '0'}};
    Solution t;
    cout << t.maximalRectangle(maxtrix);
    return 0;
}