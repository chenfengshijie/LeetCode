#include <stack>
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

// Ford–Fulkerson 增广路算法：EK DINIC  ISAP

/**
 * @brief 使用BFS寻找增广路
 *
 */
class EK
{
public:
    static const int MAXN = 10009;
    int n, m; // n 个点，m 条边

    // 前向星存图
    int head[MAXN], edge_count = 0;
    int next[MAXN], cap[MAXN], to[MAXN], flow[MAXN];
    // BFS array
    int pre[MAXN], dis[MAXN];

    EK()
    {
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        memset(cap, 0, sizeof(cap));
        memset(to, 0, sizeof(to));
        memset(flow, 0, sizeof(flow));
        memset(pre, -1, sizeof(pre));
        memset(dis, 0, sizeof(dis));
    }

    void add_edge(int u, int v, int cap1)
    {
        next[edge_count] = head[u];
        head[u] = edge_count;
        to[edge_count] = v;
        cap[edge_count] = cap1;
        edge_count++;
    }

    void BFS(int u, int v)
    {
        std::queue<int> q;
        q.push(u);
        int cnt;
        memset(dis, 0, sizeof(dis));
        dis[u] = INT_MAX;
        while (!q.empty())
        {
            cnt = q.front();
            q.pop();
            for (int i = head[cnt]; i != -1; i = next[i])
            {
                if (!dis[to[i]] && cap[i] > flow[i])
                {
                    dis[to[i]] = std::min(dis[cnt], cap[i] - flow[i]);
                    pre[to[i]] = i;
                    q.push(to[i]);
                }
            }
            if (dis[v])
                break;
        }
    }

    long long maxflow(int s, int t)
    {
        long long ans = 0;
        while (1)
        {
            BFS(s, t);
            if (!dis[t])
                break;
            else
                ans += 1ll * dis[t];
            for (int i = t; i != s; i = to[pre[i] ^ 1])
            {
                flow[pre[i]] += dis[t];
                flow[pre[i] ^ 1] -= dis[t];
            }
        }
        return ans;
    }
};

class DINIC
{
public:
    static const int MAXN = 10009;
    int n, m, s, t;
    int head[MAXN], edge_count = 0, next[MAXN], cap[MAXN], to[MAXN], flow[MAXN];

    int dep[MAXN], cur[MAXN];

    void add_edge(int u, int v, int cap1)
    {
        next[edge_count] = head[u];
        head[u] = edge_count;
        to[edge_count] = v;
        cap[edge_count] = cap1;
        edge_count++;
    }
    DINIC()
    {
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        memset(cap, 0, sizeof(cap));
        memset(to, 0, sizeof(to));
        memset(flow, 0, sizeof(flow));
        memset(dep, 0, sizeof(dep));
    }
    bool BFS(const int s)
    {
        std::queue<int> q;
        q.push(s);
        memset(dep, -1, sizeof(dep));
        dep[s] = 0;
        while (!q.empty())
        {
            int cnt = q.front();
            q.pop();
            for (int i = head[cnt]; i != -1; i = next[i])
            {
                if (dep[to[i]] == -1 && cap[i] > flow[i])
                {
                    dep[to[i]] = dep[cnt] + 1;
                    q.push(to[i]);
                }
            }
        }
        return dep[t] != -1;
    }
    int DFS(int u, int current_flow)
    {
        if (u == t || !current_flow)
        {
            return current_flow;
        }
        int ans = 0;
        for (int i = cur[u]; i != -1; i = next[i])
        {
            cur[u] = next[i];
            if (dep[to[i]] == dep[u] + 1)
            {
                int tmp = DFS(to[i], std::min(current_flow, cap[i] - flow[i]));
                if (tmp)
                {
                    flow[i] += tmp;
                    flow[i ^ 1] -= tmp;
                    ans += tmp;
                    current_flow -= tmp;
                    if (current_flow == 0)
                        break;
                }
            }
        }
        return ans;
    }
    long long maxflow()
    {
        long long ans = 0;
        while (BFS(s))
        {
            for (int i = 1; i <= n; i++)
                cur[i] = head[i];
            ans += DFS(s, INT_MAX >> 1);
        }
        return ans;
    }
};

class ISAP
{
    struct Edge
    {
        int from, to, cap, flow;

        Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f){};
        bool operator<(const Edge &b) const
        {
            return from < b.from || (from == b.from && to < b.to);
        }
    };
    static const int maxn = 10009;
    int n, m, s, t;
    std::vector<Edge> edges;
    std::vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];
    int p[maxn];
    int num[maxn];

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        std::queue<int> Q;
        Q.push(t);
        vis[t] = 1;
        d[t] = 0;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); i++)
            {
                Edge &e = edges[G[x][i] ^ 1];
                if (!vis[e.from] && e.cap > e.flow)
                {
                    vis[e.from] = 1;
                    d[e.from] = d[x] + 1;
                    Q.push(e.from);
                }
            }
        }
        return vis[s];
    }

    void init(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++)
            G[i].clear();
        edges.clear();
    }

    int Augment()
    {
        int x = t, a = INT_MAX;
        while (x != s)
        {
            Edge &e = edges[p[x]];
            a = std::min(a, e.cap - e.flow);
            x = edges[p[x]].from;
        }
        x = t;
        while (x != s)
        {
            edges[p[x]].flow += a;
            edges[p[x] ^ 1].flow -= a;
            x = edges[p[x]].from;
        }
        return a;
    }

    int Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++)
            num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while (d[s] < n)
        {
            if (x == t)
            {
                flow += Augment();
                x = s;
            }
            int ok = 0;
            for (int i = cur[x]; i < G[x].size(); i++)
            {
                Edge &e = edges[G[x][i]];
                if (e.cap > e.flow && d[x] == d[e.to] + 1)
                {
                    ok = 1;
                    p[e.to] = G[x][i];
                    cur[x] = i;
                    x = e.to;
                    break;
                }
            }
            if (!ok)
            {
                int m = n - 1;
                for (int i = 0; i < G[x].size(); i++)
                {
                    Edge &e = edges[G[x][i]];
                    if (e.cap > e.flow)
                        m = std::min(m, d[e.to]);
                }
                if (--num[d[x]] == 0)
                    break;
                num[d[x] = m + 1]++;
                cur[x] = 0;
                if (x != s)
                    x = edges[p[x]].from;
            }
        }
        return flow;
    }
};

///! 基于推送重贴标签的预流推进算法

class HLPP
{
public:
    static const int MAXN = 100009;
    int head[MAXN], next[MAXN], to[MAXN], cap[MAXN], flow[MAXN];
    long long ex[MAXN], edge_count = 0;
    int n, m, s, t;
    int height[MAXN], gap[MAXN], cur[MAXN];
    int level = 0; // 溢出节点的最高高度
    std::stack<int> B[MAXN];

    void add_edge(int u, int v, int cap1)
    {
        next[edge_count] = head[u];
        head[u] = edge_count;
        to[edge_count] = v;
        cap[edge_count] = cap1;
        flow[edge_count] = 0;
        edge_count++;
    }
    HLPP()
    {
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        memset(cap, 0, sizeof(cap));
        memset(to, 0, sizeof(to));
        memset(flow, 0, sizeof(flow));
    }
    bool bfs_init()
    {
        memset(height, 0x3f, sizeof(height));
        std::queue<int> q;
        q.push(t);
        height[t] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = next[i])
            {
                int v = to[i];
                if (height[v] == 0x3f3f3f3f && cap[i ^ 1] > 0)
                {
                    height[v] = height[u] + 1;
                    q.push(v);
                }
            }
        }
        return height[s] <= n;
    }

    int push(int u)
    {
        const int INF = 0x3f3f3f3f; // 尽可能通过能够推送的边推送超额流
        bool init = (u == s);       // 是否在初始化
        for (int i = head[u]; i != -1; i = next[i])
        {
            const int v = to[i], w = cap[i] - flow[i];
            if (!w || (init == false && height[u] != height[v] + 1) ||
                height[u] == INF) // 初始化时不考虑高度差为1
                continue;
            long long k = init ? w : std::min(1ll * w, ex[u]);
            // 取到剩余容量和超额流的最小值，初始化时可以使源的溢出量为负数。
            if (v != s && v != t && !ex[v])
                B[height[v]].push(v), level = std::max(level, height[v]);
            ex[u] -= k, ex[v] += k, flow[i] += k, flow[i ^ 1] -= k; // push
            if (!ex[u])
                return 0; // 如果已经推送完就返回
        }
        return 1;
    }
    void relabel(int u)
    { // 重贴标签（高度）
        height[u] = 0x3f3f3f3f;
        for (int i = head[u]; i != -1; i = next[i])
            if (cap[i] > flow[i])
                height[u] = std::min(height[u], height[to[i]]);
        if (++height[u] < n)
        { // 只处理高度小于 n 的节点
            B[height[u]].push(u);
            level = std::max(level, height[u]);
            ++gap[height[u]]; // 新的高度，更新 gap
        }
    }
    int select()
    {
        while (B[level].size() == 0 && level > -1)
            level--;
        return level == -1 ? -1 : B[level].top();
    }
    long long maxflow()
    {
        if (!bfs_init())
            return 0;
        memset(gap, 0, sizeof(gap));
        for (int i = 1; i <= n; i++)
            if (height[i] != 0x3f3f3f3f)
            {
                gap[height[i]]++;
            }

        height[s] = n;
        push(s);
        int u;
        while ((u = select()) != -1)
        {
            B[level].pop();
            // 删除不与t联通的点
            if (height[u] > n)
                continue;
            if (push(u))
            {
                --gap[height[u]];
                if (!gap[height[u]])
                {
                    for (int i = 1; i <= n; i++)
                        if (i != s && i != t && height[i] > height[u] && height[i] < n + 1)
                        {
                            height[i] = n + 1;
                            --gap[height[i]];
                        }
                }
                relabel(u);
            }
        }
        return ex[t];
    }
};
HLPP hlpp;
int main()
{

    scanf("%d%d%d%d", &hlpp.n, &hlpp.m, &hlpp.s, &hlpp.t);
    for (int i = 0; i < hlpp.m; i++)
    {
        int u, v, cap;
        scanf("%d%d%d", &u, &v, &cap);
        hlpp.add_edge(u, v, cap);
        hlpp.add_edge(v, u, 0);
    }
    printf("%lld\n", hlpp.maxflow());
    return 0;
}