#include <iostream>
#include <vector>

/**
 * @brief 两次DFS求解树的直径，只能用于不存在负权值的树中
 *
 */
class TreeDiameter
{
public:
    std::vector<std::vector<int>> G;
    std::vector<int> dist;
    int n, m;
    int getDiameter()
    {
        dist[1] = 0;
        DFS(1, 0);
        dist[maxpoint] = 0;
        DFS(maxpoint, 0);
        return dist[maxpoint];
    }
    void input_data()
    {
        scanf("%d", &m);
        int u, v;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }

private:
    int maxpoint;
    void DFS(int p, int fa)
    {
        for (int v : G[p])
        {
            if (v != fa)
            {
                dist[v] = dist[p] + 1;
                if (dist[v] > dist[maxpoint])
                {
                    maxpoint = v;
                }
                DFS(v, p);
            }
        }
    }
};

class TreeDiameterDP
{
public:
    std::vector<std::vector<int>> G;
    std::vector<int> dist;
    int n, m;
    int getDiameter()
    {
        dist1.resize(n + 1);
        dist2.resize(n + 1);
        DP(1, 0);
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans = std::max(ans, dist1[i] + dist2[i]);
        }
        return ans;
    }
    void input_data()
    {
        int u, v;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }

private:
    std::vector<int> dist1, dist2;
    void DP(int p, int fa)
    {
        dist1[p] = dist2[p] = 0;
        for (int v : G[p])
        {
            if (v != fa)
            {
                DP(v, p);
                if (dist1[v] + 1 > dist1[p])
                {
                    dist2[p] = dist1[p];
                    dist1[p] = dist1[v] + 1;
                }
                else if (dist1[v] + 1 > dist2[p])
                {
                    dist2[p] = dist1[v] + 1;
                }
            }
        }
    }
};