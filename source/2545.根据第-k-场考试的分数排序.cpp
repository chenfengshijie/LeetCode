/*
 * @lc app=leetcode.cn id=2545 lang=cpp
 *
 * [2545] 根据第 K 场考试的分数排序
 */

// @lc code=start
#include <vector>
#include <algorithm>
using std::vector;
class Solution
{
public:
    vector<vector<int>> sortTheStudents(vector<vector<int>> &score, int k)
    {
        auto cmp = [=](vector<int> &a, vector<int> &b)
        { return a[k] > b[k]; };
        std::sort(score.begin(), score.end(), cmp);
        return score;
    }
};
// @lc code=end
