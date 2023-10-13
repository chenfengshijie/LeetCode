#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
class Solution
{
public:
    static const int MAXN = 3009;
    int n, p;
    std::vector<int> G[MAXN << 1];
    int cost[MAXN];
    void add_edge(int u, int v)
    {
        G[u].push_back(v);
    }
    int dfn[MAXN], low[MAXN], time_stamp = 0, in_stack[MAXN], scc_cnt = 0;
    std::vector<int> scc[3009];
    int belong[MAXN];
    std::stack<int> s;
    int in[MAXN];
    void tarjan(int p)
    {
        dfn[p] = low[p] = ++time_stamp;
        s.push(p), in_stack[p] = 1;
        for (int i = 0; i < G[p].size(); i++)
        {
            int v = G[p][i];
            if (!dfn[v])
            {
                tarjan(v);
                low[p] = std::min(low[p], low[v]);
            }
            else if (in_stack[v])
            {
                low[p] = std::min(low[p], dfn[v]);
            }
        }
        if (dfn[p] == low[p])
        {
            scc_cnt++;
            int x;
            do
            {
                x = s.top();
                s.pop();
                in_stack[x] = 0;
                scc[scc_cnt].push_back(x);
                belong[x] = scc_cnt;
            } while (x != p);
        }
    }
    int solve()
    {
        tarjan(1);
        memset(in, 0, sizeof(in));
        for (int i = 1; i <= scc_cnt; i++)
        {
            for (int j = 0; j < scc[i].size(); j++)
            {
                int v = scc[i][j];
                in[belong[v]]++;
            }
        }
        int ans = 0, tmp, minNode, flag = 0;
        for (int i = 1; i <= scc_cnt; i++)
        {
            if (!in[1])
            {
                tmp = INT_MAX;
                for (int j = 0; j < scc[i].size(); j++)
                {
                    int v = scc[i][j];
                    tmp = std::min(tmp, cost[v]);
                }
                if (tmp == INT_MAX)
                {
                    for (int j = 0; j < scc[i].size(); j++)
                        minNode = std::min(minNode, scc[i][j]);
                    flag = 1;
                }

                ans += tmp;
            }
        }
        if (flag)
        {
            printf("NO\n");
            printf("%d", minNode);
        }
        else
        {
            printf("YES\n");
            printf("%d", ans);
        }
    }
};

Solution t;
int main()
{
    scanf("%d%d", &t.n, &t.p);
    int a, b;
    for (int i = 0; i < t.p; i++)
    {
        scanf("%d%d", &a, &b);
        t.cost[a] = b;
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        t.add_edge(a, b);
    }
    t.solve();
    return 0;
}