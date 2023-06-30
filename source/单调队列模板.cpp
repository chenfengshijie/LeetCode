/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief luogu P1886 单调队列模板题
 * @version 0.1
 * @date 2023-06-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <cstdio>
#include <queue>
const int MAXN = 1000009;
using namespace std;
int n, k;
int num[MAXN], ans_min[MAXN], ans_max[MAXN];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", num + i);

    deque<int> maxq, minq;
    for (int i = 0; i < n; i++)
    {
        while (!maxq.empty() && maxq.front() <= i - k)
            maxq.pop_front();
        while (!minq.empty() && minq.front() <= i - k)
            minq.pop_front();
        while (!maxq.empty() && num[maxq.back()] <= num[i])
            maxq.pop_back();
        maxq.push_back(i);
        while (!minq.empty() && num[minq.back()] >= num[i])
            minq.pop_back();
        minq.push_back(i);
        if (i >= k - 1)
        {
            ans_max[i - k + 1] = maxq.front();
            ans_min[i - k + 1] = minq.front();
        }
    }
    for (int i = 0; i <= n - k; i++)
        printf("%d ", num[ans_min[i]]);
    printf("\n");
    for (int i = 0; i <= n - k; i++)
        printf("%d ", num[ans_max[i]]);
    return 0;
}