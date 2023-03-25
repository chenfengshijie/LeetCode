/*
 * @lc app=leetcode.cn id=2546 lang=cpp
 *
 * [2546] 执行逐位运算使字符串相等
 */

// @lc code=start
#include <string>
using std::string;
class Solution
{
public:
    bool makeStringsEqual(string s, string target)
    {
        if (s == target)
            return true;
        if ((s.find('1') != s.npos && target.find('1') != target.npos) || (s.find('1') == s.npos && target.find('1') == target.npos))
            return true;
        return false;
    }
};
// @lc code=end