/*
 * @lc app=leetcode.cn id=52 lang=cpp
 *
 * [52] N 皇后 II
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
    int totalNQueens(int n)
    {
        que.resize(10);
        for (int i = 0; i < 13; i++)
            flag.push_back(que);
        DFS(n, 0);
        return ans;
    }

private:
    vector<vector<int>> flag;
    vector<int> que;
    int ans = 0;
    void DFS(const int n, const int p)
    {
        if (p == n)
        {
            ++ans;
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
            for (int j = 0; j < 3; j++)
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
    std::cout << t.totalNQueens(4);
    return 0;
}