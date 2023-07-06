/**
 * @file 费用流.cpp 将最大流算法的寻找增广路的搜索算法换成最短路算法即可。
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <cstdio>
#include <queue>
#include <climits>

class EKMincost
{
public:
    static const int MAXN = 10009;
    int n, m; // n 个点，m 条边

    // 前向星存图
    int head[MAXN], edge_count = 0;
    int next[MAXN], cap[MAXN], to[MAXN], flow[MAXN], cost[MAXN];
    // BFS array
    int pre[MAXN], dis[MAXN], inque[MAXN], incf[MAXN];

    EKMincost()
    {
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        memset(cap, 0, sizeof(cap));
        memset(to, 0, sizeof(to));
        memset(flow, 0, sizeof(flow));
        memset(pre, -1, sizeof(pre));
        memset(dis, 0, sizeof(dis));
    }

    void add_edge(int u, int v, int cap1, int cost1)
    {
        next[edge_count] = head[u];
        head[u] = edge_count;
        to[edge_count] = v;
        cap[edge_count] = cap1;
        cost[edge_count] = cost1;
        edge_count++;
    }

    void spfa(int u, int v)
    {
        std::queue<int> q;
        memset(dis, 0x3f, sizeof(dis));
        q.push(u);
        dis[u] = 0;
        inque[u] = 1;
        incf[u] = INT_MAX;
        incf[v] = 0;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            inque[x] = 0;
            for (int i = head[x]; i != -1; i = next[i])
            {
                int y = to[i];
                if (cap[i] > flow[i] && dis[y] > dis[x] + cost[i])
                {
                    dis[y] = dis[x] + cost[i];
                    pre[y] = i;
                    incf[y] = std::min(incf[x], cap[i] - flow[i]);
                    if (!inque[y])
                    {
                        q.push(y);
                        inque[y] = 1;
                    }
                }
            }
        }
    }

    std::pair<long long, long> maxflow(int s, int t)
    {
        long long ans = 0;
        long long mincost = 0;
        while (1)
        {
            spfa(s, t);
            if (!incf[t])
                break;
            else
                ans += 1ll * incf[t];
            for (int i = t; i != s; i = to[pre[i] ^ 1])
            {
                flow[pre[i]] += incf[t];
                flow[pre[i] ^ 1] -= incf[t];
                mincost += 1ll * incf[t] * cost[pre[i]];
            }
        }
        return std::make_pair(ans, mincost);
    }
};
class DINIC
{
public:
    static const int MAXN = 100009;
    int n, m, s, t;
    int head[MAXN], edge_count = 0, next[MAXN], cap[MAXN], to[MAXN], flow[MAXN], cost[MAXN];

    int dis[MAXN], cur[MAXN], inque[MAXN];

    void add_edge(int u, int v, int cap1, int cost1)
    {
        next[edge_count] = head[u];
        head[u] = edge_count;
        to[edge_count] = v;
        cap[edge_count] = cap1;
        cost[edge_count] = cost1;
        edge_count++;
    }
    DINIC()
    {
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        memset(cap, 0, sizeof(cap));
        memset(to, 0, sizeof(to));
        memset(flow, 0, sizeof(flow));
        memset(dis, 0, sizeof(dis));
    }

    int spfa(int u)
    {
        std::queue<int> q;

        for (int i = 0; i <= n; i++)
        {
            dis[i] = INT_MAX >> 1;
            inque[i] = 0;
        }
        q.push(u);
        dis[u] = 0;
        inque[u] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            inque[x] = 0;
            for (int i = head[x]; i != -1; i = next[i])
            {
                int y = to[i];
                if (flow[i] < cap[i] && dis[y] > dis[x] + cost[i])
                {
                    dis[y] = dis[x] + cost[i];
                    if (!inque[y])
                    {
                        inque[y] = 1;
                        q.push(y);
                    }
                }
            }
        }
        return dis[t] != INT_MAX;
    }

    int DFS(int u, int current_flow, int &current_cost)
    {
        inque[u] = 1;
        if (u == t || !current_flow)
        {
            return current_flow;
        }
        int ans = 0;
        for (int i = cur[u]; i != -1; i = next[i])
        {
            cur[u] = next[i];

            if (!inque[to[i]] && flow[i] < cap[i] && dis[to[i]] == dis[u] + cost[i])
            {
                int tmp = DFS(to[i], std::min(current_flow, cap[i] - flow[i]), current_cost);
                if (tmp)
                {
                    flow[i] += tmp;
                    flow[i ^ 1] -= tmp;
                    ans += tmp;
                    current_flow -= tmp;
                    current_cost += tmp * cost[i];
                    if (current_flow == 0)
                        break;
                }
            }
        }
        return ans;
    }
    std::pair<long long, long long> maxflow()
    {
        long long flow = 0;
        long long cost = 0;
        int current_cost = 0;
        int current_flow = 0;
        while (spfa(s))
        {
            for (int i = 1; i <= n; i++)
                cur[i] = head[i];
            current_cost = 0;
            current_flow = DFS(s, INT_MAX >> 1, current_cost);
            cost += 1ll * current_cost;
            if (current_flow == 0)
                break;
            flow += 1ll * current_flow;
        }
        return std::make_pair(flow, cost);
    }
};

DINIC dinic;

int main()
{
    freopen(R"(C:\Users\FrozeWorld\.leetcode\input.txt)", "r", stdin);
    scanf("%d%d%d%d", &dinic.n, &dinic.m, &dinic.s, &dinic.t);
    for (int i = 0; i < dinic.m; i++)
    {
        int u, v, f, c;
        scanf("%d%d%d%d", &u, &v, &f, &c);
        dinic.add_edge(u, v, f, c);
        dinic.add_edge(v, u, 0, -c);
    }
    auto ans = dinic.maxflow();
    printf("%lld %lld", ans.first, ans.second);
    return 0;
}