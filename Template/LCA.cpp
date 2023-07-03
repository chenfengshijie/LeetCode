#include <iostream>
#include <vector>
#include <map>

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class LCA
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
    LCA(const vector<vector<int>> &adjList, int root)
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