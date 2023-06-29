/*
 * @lc app=leetcode.cn id=57 lang=cpp
 *
 * [57] 插入区间
 */
#include <vector>
#include <algorithm>
using std::vector;
// @lc code=start
class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> ans;
        int left = newInterval[0], right = newInterval[1];
        bool flag = 0;
        for (auto &interval : intervals)
        {
            if (interval[0] > right)
            {

                if (!flag)
                {
                    ans.push_back({left, right});
                    flag = 1;
                }
                ans.push_back(interval);
            }
            else if (interval[1] < left)
            {
                ans.push_back(interval);
            }
            else
            {
                left = std::min(left, interval[0]);
                right = std::max(right, interval[1]);
            }
        }
        if (!flag)
        {
            ans.push_back({left, right});
        }
        return ans;
    }
};
// @lc code=end
