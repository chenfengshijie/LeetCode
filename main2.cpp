#include <queue>
#include <stdio.h>
#include <cstring>
#define INF 2147483467
using namespace std;
using ll = long long;

const int maxn = 520010, maxm = 520010;
int n, m, s, t;
int height[maxn], inqueue[maxn], gap[maxn * 2 + 1000];
ll left[maxn];
struct node
{
    int x;
    node(int a) : x(a) {}
    inline bool operator<(const node &n)
    {
        return height[x] < height[n.x];
    }
    inline operator int() const
    {
        return x;
    }
};
priority_queue<node, vector<node>> q;

struct Edge
{
    int to, next;
    ll weight;
};
Edge edges[maxm];
int edge_cnt = 1, head[maxn];

void add(int x, int y, ll w)
{
    edges[++edge_cnt].next = head[x];
    edges[edge_cnt].to = y;
    edges[edge_cnt].weight = w;
    head[x] = edge_cnt;
}

void bfs()
{
    memset(height, -1, sizeof(height));
    memset(gap, 0, sizeof(gap));
    queue<int> q1;
    q1.push(t);
    height[t] = 0;
    ++(gap[0]);
    while (!q1.empty())
    {
        int front = q1.front();
        q1.pop();
        for (int i = head[front]; i != 0; i = edges[i].next)
        {
            ll v = edges[i].to, vol = edges[i].weight;
            if (vol == 0 && height[v] == -1)
            {
                height[v] = height[front] + 1;
                ++(gap[height[v]]);
                q1.push(v);
            }
        }
    }
}

void relabel(int x)
{
    --(gap[height[x]]);
    if (gap[height[x]] == 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (height[i] > height[x] && i != s && i != t)
            {
                --(gap[height[i]]);
                height[i] = n + 1;
            }
        }
    }
    height[x] = 3 * maxn;
    for (int i = head[x]; i != 0; i = edges[i].next)
    {
        ll v = edges[i].to, vol = edges[i].weight;
        if (vol > 0 && height[v] + 1 < height[x])
        {
            height[x] = height[v] + 1;
        }
    }
    ++(gap[height[x]]);
}

ll hlpp()
{
    bfs();
    height[s] = n;
    for (int i = head[s]; i != 0; i = edges[i].next)
    {
        ll v = edges[i].to, vol = edges[i].weight;
        if (vol > 0)
        {
            left[v] += vol;
            edges[i].weight -= vol;
            edges[i ^ 1].weight += vol;
        }
        if (v != t && v != s && !inqueue[v])
        {
            q.push(v);
            inqueue[v] = 1;
        }
    }
    while (!q.empty())
    {
        int u = q.top();
        q.pop();
        inqueue[u] = 0;
        for (int i = head[u]; i != 0; i = edges[i].next)
        {
            int v = edges[i].to;
            ll vol = edges[i].weight;
            if (height[v] + 1 == height[u] && vol > 0)
            {
                int flow = min(vol, left[u]);
                left[u] -= flow;
                left[v] += flow;
                edges[i].weight -= flow;
                edges[i ^ 1].weight += flow;
                if (!inqueue[v] && v != s && v != t)
                {
                    q.push(v);
                    inqueue[v] = 1;
                }
            }
            if (left[u] == 0)
                break;
        }
        if (left[u] != 0)
        {
            relabel(u);
            q.push(u);
            inqueue[u] = 1;
        }
    }
    return left[t];
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        ll w;
        scanf("%d %d %lld", &x, &y, &w);
        add(x, y, w);
        add(y, x, 0);
    }
    printf("%lld", hlpp());
    return 0;
}