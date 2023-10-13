/**
 * @file 最长子序列.cpp
 * @author chenfeng ()
 * @brief https://www.cnblogs.com/itlqs/p/5743114.html
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */

/// 基于动态规划的算法

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
const int MAXSIZE = 100009;
int num[MAXSIZE];
int increase[MAXSIZE]; /// 该数组保存不断增长的子序列，并不是最终答案
int n;
void solve()
{
    for (int i = 0; i < n; i++)
        scanf("%d", num + i);
    int len = 0;
    for (int i = 0; i < n; ++i)
    {
        int pos = lower_bound(increase, increase + len, num[i]) - increase;
        increase[pos] = num[i];
        if (pos == len)
            len++;
    }
    printf("%d\n", len);
}
inline int lowbit(int x)
{
    return x & -x;
}
int bit[MAXSIZE];
void add(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        bit[i] += v;
}
int query(int k)
{
    int res = 0;
    for (int i = k; i > 0; i -= lowbit(i))
        res += bit[i];
}
void solve2()
{
    vector<pair<int, int>> Ele;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", num + i);
        Ele.push_back({num[i], i});
    }
    sort(Ele.begin(), Ele.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.first < b.first; });
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int pos = Ele[i].second;
        int res = query(pos);
        ans = max(ans, res + 1);
        add(pos, 1);
    }
    printf("%d\n", ans);
}
