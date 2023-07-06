#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 构建ST表
vector<vector<int>> buildSTTable(const vector<int> &arr)
{
    int n = arr.size();
    int logN = log2(n) + 1;

    vector<vector<int>> st(logN, vector<int>(n));

    // 初始化ST表第一列
    for (int i = 0; i < n; i++)
    {
        st[i][0] = arr[i];
    }

    // 动态规划地填充ST表
    for (int j = 1; j < logN; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            // 区间范围的两个子区间的大小相等
            st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    return st;
}

// 查询ST表，返回区间的最小值
int querySTTable(const vector<vector<int>> &st, int left, int right)
{
    int j = log2(right - left + 1);
    int minVal = min(st[j][left], st[j][right - (1 << j) + 1]);
    return minVal;
}
