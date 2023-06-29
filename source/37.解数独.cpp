/*
 * @lc app=leetcode.cn id=37 lang=cpp
 *
 * [37] 解数独
 */
#include <vector>
using std::vector;
// @lc code=start
#define belong(x, y) (x / 3 * 3 + y / 3)
class Solution
{
public:
    int chunk[19][19];
    int line[19][19];
    int col[19][19];
    int flag = false;
    vector<vector<char>> ans;
    void solveSudoku(vector<vector<char>> &board)
    {
        memset(chunk, 0, sizeof(chunk));
        memset(line, 0, sizeof(line));
        memset(col, 0, sizeof(col));
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int cnt = board[i][j] - '0';
                    line[i][cnt] = 1;
                    col[j][cnt] = 1;
                    chunk[belong(i, j)][cnt] = 1;
                }
            }
        DFS(0, 0, board);
        board = ans;
        return;
    }

private:
    void DFS(int x, int y, vector<vector<char>> &board)
    {
        if (flag)
            return;
        int found = 0;
        for (int i = x; i < 10; i++)
        {
            if (found)
                break;
            for (int j = (i == x ? y : 0); j < 9; j++)
            {
                if (found)
                    break;
                if (i == 9)
                {
                    flag = true;
                    ans = board;
                    return;
                }
                if (board[i][j] == '.')
                {
                    found = 1;
                    for (int k = 1; k < 10; k++)
                        if (!line[i][k] && !col[j][k] && !chunk[belong(i, j)][k])
                        {
                            line[i][k] = 1;
                            col[j][k] = 1;
                            chunk[belong(i, j)][k] = 1;
                            board[i][j] = '0' + k;
                            DFS(i, j, board);
                            line[i][k] = 0;
                            col[j][k] = 0;
                            chunk[belong(i, j)][k] = 0;
                            board[i][j] = '.';
                        }
                }
            }
        }
        return;
    }
};
// @lc code=end
int main()
{
    Solution t;
    vector<vector<char>>
        ss =
            {
                {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    t.solveSudoku(ss);
    return 0;
}
