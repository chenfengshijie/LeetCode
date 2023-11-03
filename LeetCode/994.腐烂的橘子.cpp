#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

class Solution
{
public:
    int orangesRotting(std::vector<std::vector<int>> &grid)
    {
        queue<pair<int, int>> q;
        int n = grid.size(), m = grid[0].size();
        int ans = 0, good = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 2)
                    q.emplace(i, j);
                else if (grid[i][j] == 1)
                    good++;
        if (good == 0)
            return 0;
        q.emplace(-1, -1);
        while (good > 0 && q.size() != 1)
        {
            int x, y;
            tie(x, y) = q.front();
            if (x == -1 && y == -1)
            {
                ++ans;
                q.emplace(-1, -1);
                q.pop();
                continue;
            }
            q.pop();
            constexpr int dx[4] = {0, 1, 0, -1};
            constexpr int dy[4] = {1, 0, -1, 0};
            for (int i = 0; i < 4; i++)
            {
                int x_ = x + dx[i];
                int y_ = y + dy[i];
                if (x_ >= 0 && x_ < n && y_ >= 0 && y_ < m)
                {
                    if (grid[x_][y_] == 1)
                    {
                        good--;
                        grid[x_][y_] = 2;
                        q.emplace(x_, y_);
                    }
                }
            }
        }
        if (good == 0)
            return ans + 1;
        return -1;
    }
};
