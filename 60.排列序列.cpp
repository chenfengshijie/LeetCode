/*
 * @lc app=leetcode.cn id=60 lang=cpp
 *
 * [60] 排列序列
 */
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
// @lc code=start
class Solution
{
public:
    string getPermutation(int n, int k)
    {
        if (n == 1)
            return "1";
        k--;
        vector<int> fact(n + 10, 0);
        vector<int> used(n + 10, 0);
        fact[0] = 0;
        fact[2] = 2;
        fact[1] = 1;
        for (int i = 3; i < 10; i++)
            fact[i] = fact[i - 1] * i;
        int order[20];
        for (int i = n - 1; i > 0; i--)
        {
            order[i] = k / fact[i];
            k -= fact[i] * order[i];
        }
        order[0] = 0;
        string ans;
        for (int i = n - 1; i >= 0; i--)
        {
            int cnt = 0;
            for (int j = 1; j <= n; j++)
            {
                if (used[j])
                    continue;
                else
                {
                    if (cnt == order[i])
                    {
                        used[j] = 1;
                        ans.push_back('0' + j);
                        break;
                    }
                    else
                        ++cnt;
                }
            }
        }
        return ans;
    }
};
// @lc code=end
Solution t;
int main()
{
    auto ans = t.getPermutation(2, 1);
    std::cout << ans;
    return 0;
}