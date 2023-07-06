#include <vector>
#include <unordered_set>
using namespace std;
/*给你一个下标从 0 开始、大小为 m x n 的二维矩阵 grid ，请你求解大小同样为 m x n 的答案矩阵 answer 。

矩阵 answer 中每个单元格 (r, c) 的值可以按下述方式进行计算：

令 topLeft[r][c] 为矩阵 grid 中单元格 (r, c) 左上角对角线上 不同值 的数量。
令 bottomRight[r][c] 为矩阵 grid 中单元格 (r, c) 右下角对角线上 不同值 的数量。
然后 answer[r][c] = |topLeft[r][c] - bottomRight[r][c]| 。

返回矩阵 answer 。

矩阵对角线 是从最顶行或最左列的某个单元格开始，向右下方向走到矩阵末尾的对角线。

如果单元格 (r1, c1) 和单元格 (r, c) 属于同一条对角线且 r1 < r ，则单元格 (r1, c1) 属于单元格 (r, c) 的左上对角线。类似地，可以定义右下对角线。*/

class Solution
{
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>> &grid)
    {
        vector<vector<int>> answer(grid.size(), vector<int>(grid[0].size(), 0));
        int n = grid.size(), m = grid[0].size();
        auto cal_topleft = [&](int x, int y) -> int
        {
            unordered_set<int> s;
            for (int i = 1; i < n; i++)
            {
                int x_ = x - i;
                int y_ = y - i;
                if (x_ < 0 || y_ < 0)
                    break;
                s.insert(grid[x_][y_]);
            }

            return s.size();
        };
        auto cal_bottomright = [&](int x, int y) -> int
        {
            unordered_set<int> s;
            for (int i = 1; i < n; i++)
            {
                int x_ = x + i;
                int y_ = y + i;
                if (x_ >= n || y_ >= m)
                    break;
                s.insert(grid[x_][y_]);
            }
            return s.size();
        };

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                answer[i][j] = abs(cal_topleft(i, j) - cal_bottomright(i, j));
            }
        return answer;
    }
};

int main()
{
}