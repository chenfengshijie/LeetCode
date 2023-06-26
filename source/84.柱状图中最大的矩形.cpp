/*
 * @lc app=leetcode.cn id=84 lang=cpp
 *
 * [84] 柱状图中最大的矩形
 */

#include <vector>
#include <stack>
using std::vector;
// @lc code=start
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> left(n, 0), right(n, n);
        std::stack<int> s1;
        for (int i = 0; i < n; i++)
        {
            while (!s1.empty() && heights[s1.top()] > heights[i])
            {
                right[s1.top()] = i;
                s1.pop();
            }
            left[i] = s1.empty() ? -1 : s1.top();
            s1.push(i);
        }
        int ans = -1;
        for (int i = 0; i < n; i++)
            ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);
        return ans;
    };
};
// @lc code=end

int main()
{
    Solution t;
    vector<int> c{2, 4};
    t.largestRectangleArea(c);
    return 0;
}
