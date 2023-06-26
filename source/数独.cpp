#include <iostream>
#include <cstring>
int ans[10][10];
/**
 * @brief 用于解决精确覆盖和重复覆盖问题的DLX算法
 *
 */
struct DLX
{
    static const int N = 1009;
    static const int MAXSIZE = 1000009; // 最多具备多少个1
    int first[N], siz[N], stack[N];
    int n, m, tot;
    int L[MAXSIZE], R[MAXSIZE], U[MAXSIZE], D[MAXSIZE];
    int col[MAXSIZE], row[MAXSIZE];
    /**
     * @brief 构造一个r行c列的DanceLink，并且初始化c个列节点
     *
     * @param r row
     * @param c Column
     */
    void build(const int &r, const int &c)
    {
        n = r, m = c;
        tot = c;
        for (int i = 0; i <= c; i++)
        {
            L[i] = i - 1;
            R[i] = i + 1;
            U[i] = D[i] = i;
        }
        L[0] = c;
        R[c] = 0; // 保证是一个环状的链表
        memset(first, 0, sizeof(first));
        memset(siz, 0, sizeof(siz));
    }
    /**
     * @brief 在第r行第c列插入一个1
     *
     * @param r
     * @param c
     */
    void insert(const int &r, const int &c)
    { // 进行insert操作
        col[++tot] = c, row[tot] = r, ++siz[c];
        D[tot] = D[c], U[D[c]] = tot, U[tot] = c, D[c] = tot;
        if (!first[r])
            first[r] = L[tot] = R[tot] = tot;
        else
        {
            R[tot] = R[first[r]], L[R[first[r]]] = tot;
            L[tot] = first[r], R[first[r]] = tot;
        }
    }
    /**
     * @brief 移除第c列
     *
     * @param c
     */
    void remove(int c)
    {
        int i, j;
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for (i = D[c]; i != c; i = D[i])
            for (j = R[i]; j != i; j = R[j])
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --siz[col[j]];
            }
    }
    /**
     * @brief 恢复第c列
     *
     * @param c
     */
    void recover(int c)
    {
        int i, j;
        for (i = U[c]; i != c; i = U[i])
            for (j = L[i]; j != i; j = L[j])
            {
                U[D[j]] = j;
                D[U[j]] = j;
                ++siz[col[j]];
            }
        L[R[c]] = c;
        R[L[c]] = c;
    }
    /**
     * @brief 递归求解
     *
     * @param dep 当前选取的个数
     * @return true
     * @return false
     */
    bool dance(int dep)
    {
        if (!R[0])
        {
            for (int i = 1; i < dep; ++i)
            {
                int x = (stack[i] - 1) / 9 / 9 + 1;
                int y = (stack[i] - 1) / 9 % 9 + 1;
                int v = (stack[i] - 1) % 9 + 1;
                ans[x][y] = v;
            }
            return true;
        }
        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i])
            if (siz[i] < siz[c])
                c = i;
        remove(c);
        int i, j;
        for (i = D[c]; i != c; i = D[i])
        {
            stack[dep] = row[i];
            for (j = R[i]; j != i; j = R[j])
                remove(col[j]);
            if (dance(dep + 1))
                return true;
            // if (dep > 82)
            //     return false;
            for (j = L[i]; j != i; j = L[j])
                recover(col[j]);
        }
        recover(c);
        return false;
    }
};
DLX solver;

int read()
{
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar()))
        f |= ch == '-';
    while (isdigit(ch))
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
} // 快读

inline int GetID(int x, int y, int num)
{
    return (x - 1) * 81 + (y - 1) * 9 + num;
}
void Insert(int row, int col, int num)
{
    int dx = (row - 1) / 3 + 1;
    int dy = (col - 1) / 3 + 1;
    int room = (dx - 1) * 3 + dy;
    int id = GetID(row, col, num);
    int f1 = (row - 1) * 9 + num;           // task 1
    int f2 = 81 + (col - 1) * 9 + num;      // task 2
    int f3 = 81 * 2 + (room - 1) * 9 + num; // task 3
    int f4 = 81 * 3 + (row - 1) * 9 + col;  // task 4
    solver.insert(id, f1);
    solver.insert(id, f2);
    solver.insert(id, f3);
    solver.insert(id, f4);
}
int main()
{
    // freopen("source\test.txt", "r", stdin);
    solver.build(729, 324);
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
        {
            scanf("%d", &ans[i][j]);
            for (int v = 1; v <= 9; ++v)
            {
                if (ans[i][j] && ans[i][j] != v)
                    continue;
                Insert(i, j, v);
            }
        }

    solver.dance(1);
    for (int i = 1; i <= 9; i++)
    {
        if (i != 1)
            printf("\n");
        for (int j = 1; j <= 9; j++)
            printf("%d ", ans[i][j]);
    }
}