/*
 * @lc app=leetcode.cn id=274 lang=cpp
 *
 * [274] H 指数
 */

// @lc code=start
#include <vector>
#include <algorithm>
using std::vector;
class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        std::sort(citations.begin(), citations.end());
        int len = citations.size();
        for (int i = 0; i < len; i++)
        {
            if (citations[i] >= (len - i))
                return len - i;
        }
        return 0;
    }
};
// @lc code=end
