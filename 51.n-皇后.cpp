/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */
#include <vector>
#include <iostream>
#include <string>
using std::string;
using std::vector;

// @lc code=start
class Solution
{
public:
    vector<vector<string>> ans;
    vector<vector<string>> solveNQueens(int n)
    {
        que.resize(19);
        for (int i = 0; i < 14; i++)
            flag.push_back(que);
        DFS(n, 0);
        return ans;
    }

private:
    vector<vector<int>> flag;
    vector<int> que;
    void DFS(const int n, const int p)
    {
        if (p == n)
        {
            vector<string> tmp;
            for (int i = 0; i < n; i++)
            {
                string s(n, '.');
                s[que[i]] = 'Q';
                tmp.push_back(s);
            }
            ans.push_back(tmp);
            return;
        }
        for (int i = 0; i < n; i++)
            if (flag[p][i] == 0)
            {
                modify(n, p, i, 1, flag);
                que[p] = i;
                DFS(n, p + 1);
                modify(n, p, i, -1, flag);
                que[p] = -1;
            }
        return;
    }
    void modify(int n, int x, int y, int InOrDe, vector<vector<int>> &flag)
    {
        int dx[] = {1, 1, 1};
        int dy[] = {1, 0, -1};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 4; j++)
            {
                int fx = x + i * dx[j], fy = y + i * dy[j];
                fx >= 0 && fx < n &&fy >= 0 && fy < n ? flag[fx][fy] += InOrDe : 0;
            }
        return;
    }
};
// @lc code=end

int main()
{
    Solution t;
    auto ans = t.solveNQueens(4);
    for (auto &x : ans)
        for (auto each : x)
            std::cout << each << std::endl;
    return 0;
}