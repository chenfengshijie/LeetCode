#include <iostream>
#include <vector>
#include <map>

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class LCAMultiply
{
private:
    vector<vector<int>> parent; // parent[i][j] 表示节点 i 往上走 2^j 步所到达的祖先节点
    vector<vector<int>> cost;   // cost[i][j] 表示节点 i 往上走 2^j 步所经过的边的权值
    vector<int> depth;          // depth[i] 表示节点 i 的深度
    int maxDepth;               // 树的最大深度

    void dfs(const vector<vector<int>> &adjList, int node, int par, int d)
    {
        parent[node][0] = par;
        cost[node][0] = 1; // 可以修改为任意的需要维护的值
        depth[node] = d;

        for (int i = 1; i <= maxDepth; i++)
        {
            int prevParent = parent[node][i - 1];
            parent[node][i] = parent[prevParent][i - 1];
            cost[node][i] = cost[node][i - 1] + cost[prevParent][i - 1];
        }

        for (int child : adjList[node])
        {
            if (child != par)
            {
                dfs(adjList, child, node, d + 1);
            }
        }
    }

public:
    LCAMultiply(const vector<vector<int>> &adjList, int root)
    {
        int numNodes = adjList.size();
        maxDepth = log2(numNodes) + 1;

        parent.resize(numNodes, vector<int>(maxDepth + 1));
        depth.resize(numNodes);

        dfs(adjList, root, -1, 0);
    }

    int getLCA(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        int ans = 0;
        // 将 u 和 v 调整到相同的深度
        int diff = depth[u] - depth[v];
        for (int i = 0; i <= maxDepth; i++)
        {
            if ((diff >> i) & 1)
            {
                ans += cost[u][i];
                u = parent[u][i];
            }
        }

        if (u == v)
            return u;

        // 同时向上跳跃，直到找到公共祖先
        for (int i = maxDepth; i >= 0; i--)
        {
            if (parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
                ans += cost[u][i] + cost[v][i];
            }
        }

        return ans;
    }
};

/**
 * @brief tarjan求LCA，主要是理解tarjan算法
 *
 */
class LCATarjan
{
    struct Edge
    {
    public:
        int toVertex, fromVertex;
        int next;
        int LCA;
        Edge() : toVertex(-1), fromVertex(-1), next(-1), LCA(-1){};
        Edge(int u, int v, int n) : fromVertex(u), toVertex(v), next(n), LCA(-1){};
    };

    static const int MAX = 100;
    int head[MAX], queryHead[MAX];
    Edge edge[MAX], queryEdge[MAX];
    int parent[MAX], visited[MAX];
    int vertexCount, edgeCount, queryCount;

    void init()
    {
        for (int i = 0; i <= vertexCount; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return find(parent[x]);
        }
    }

    void tarjan(int u)
    {
        parent[u] = u;
        visited[u] = 1;

        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            Edge &e = edge[i];
            if (!visited[e.toVertex])
            {
                tarjan(e.toVertex);
                parent[e.toVertex] = u;
            }
        }

        for (int i = queryHead[u]; i != -1; i = queryEdge[i].next)
        {
            Edge &e = queryEdge[i];
            if (visited[e.toVertex])
            {
                queryEdge[i ^ 1].LCA = e.LCA = find(e.toVertex);
            }
        }
    }
};

class LCARMQ
{
    static const int N = 10009;
    int dfn[N << 1], pos[N], tot, st[30][(N << 1) + 2], rev[30][(N << 1) + 2], depth[N << 1]; // rev表示最小深度对应的节点编号
    int lg[100];                                                                              // lg[i] 表示 i 的二进制最高位的位置
    int head[N];
    struct Edge
    {
        int next;
        int to;
        Edge(int n, int t) : next(n), to(t){};
    };
    Edge side[N << 2];
    void dfs(int cur, int dep)
    {
        dfn[++tot] = cur;
        depth[tot] = dep;
        pos[cur] = tot;
        for (int i = head[cur]; i; i = side[i].next)
        {
            int v = side[i].to;
            if (!pos[v])
            {
                dfs(v, dep + 1);
                dfn[++tot] = cur, depth[tot] = dep;
            }
        }
    }

    void init()
    {
        for (int i = 2; i <= tot + 1; ++i)
            lg[i] = lg[i >> 1] + 1; // 预处理 lg 代替库函数 log2 来优化常数
        for (int i = 1; i <= tot; i++)
            st[0][i] = depth[i], rev[0][i] = dfn[i];
        for (int i = 1; i <= lg[tot]; i++)
            for (int j = 1; j + (1 << i) - 1 <= tot; j++)
                if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)])
                    st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j];
                else
                    st[i][j] = st[i - 1][j + (1 << i - 1)],
                    rev[i][j] = rev[i - 1][j + (1 << i - 1)];
    }

    int query(int l, int r)
    {
        int k = lg[r - l + 1];
        return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l]
                                                  : rev[k][r + 1 - (1 << k)];
    }
};

class TreeSplit
{
private:
    int head[100000];
    struct Edge
    {
        int next, to;
        int len;
        Edge(int a, int b, int c) : next(a), to(b), len(c){};
    };
    void add_edge(int u, int v, int len)
    {
        edge[++edge_count] = Edge(head[u], v, len);
        head[u] = edge_count;
    }

    void DFS1(const int p, const int f, int dep)
    {
        fa[p] = f, depth[p] = dep, siz[p] = 1;
        int maxson = -1, maxsize = -1;
        for (int i = head[p]; i != 0; i = edge[i].next)
        {
            int v = edge[i].to;
            if (v == f)
                continue;
            DFS1(v, p, dep + 1);
            siz[p] += siz[v];
            if (siz[v] > maxsize)
            {
                maxsize = siz[v];
                maxson = v;
            }
        }
        if (maxsize == -1)
            son[p] = p;
        else
            son[p] = maxson;
        return;
    }

    void DFS2(int u, int f)
    {
        top[u] = f;
        dfn[u] = ++dfncnt;
        rnk[dfncnt] = u;
        if (son[u] == u)
            return;
        DFS2(son[u], f);
        for (int i = head[u]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (v != fa[u] && v != son[u])
                DFS2(v, v);
        }
    }

public:
    static const int MAXN = 100009;
    int n, m;
    Edge edge[MAXN];
    int edge_count = 0;
    int fa[MAXN];
    int depth[MAXN];
    int top[MAXN], son[MAXN], siz[MAXN];
    int dfn[MAXN], rnk[MAXN], dfncnt = 0; // 一般树链剖分会维护一个DFS序，分割的链保证DFS序连续，但在LCA用不到
    void input_data()
    {
        scanf("%d%d", &n, &m);
        int u, v, len;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%d", &u, &v, &len);
            add_edge(u, v, len);
        }
    }
    int getLCA(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (depth[top[u]] < depth[top[v]])
                v = fa[top[v]];
            else
                u = fa[top[u]];
        }
        return depth[u] > depth[v] ? v : u;
    }
};