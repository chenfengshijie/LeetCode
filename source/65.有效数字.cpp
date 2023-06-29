/*
 * @lc app=leetcode.cn id=65 lang=cpp
 *
 * [65] 有效数字
 */
#include <regex>
using std::regex;
#include <string>
using std::string;
// @lc code=start
class Solution
{
public:
    static const regex pattern;

    bool isNumber(string str)
    {
        return regex_match(str, pattern);
    }
};

const regex Solution::pattern("[+-]?(?:\\d+\\.?\\d*|\\.\\d+)(?:[Ee][+-]?\\d+)?");
// @lc code=end
