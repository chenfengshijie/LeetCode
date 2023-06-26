// #include <cstring>

// struct DLX
// {
//     static const int MAXSIZE = 1e5 + 10;
//     int n, m, tot, first[MAXSIZE + 10], siz[MAXSIZE + 10];
//     int L[MAXSIZE + 10], R[MAXSIZE + 10], U[MAXSIZE + 10], D[MAXSIZE + 10];
//     int col[MAXSIZE + 10], row[MAXSIZE + 10];
//     int stack[MAXSIZE];

//     void build(const int &r, const int &c)
//     { // 进行build操作
//         n = r, m = c;
//         for (int i = 0; i <= c; ++i)
//         {
//             L[i] = i - 1, R[i] = i + 1;
//             U[i] = D[i] = i;
//         }
//         L[0] = c, R[c] = 0, tot = c;
//         memset(first, 0, sizeof(first));
//         memset(siz, 0, sizeof(siz));
//     }

//     void insert(const int &r, const int &c)
//     { // 进行insert操作
//         col[++tot] = c, row[tot] = r, ++siz[c];
//         D[tot] = D[c], U[D[c]] = tot, U[tot] = c, D[c] = tot;
//         if (!first[r])
//             first[r] = L[tot] = R[tot] = tot;
//         else
//         {
//             R[tot] = R[first[r]], L[R[first[r]]] = tot;
//             L[tot] = first[r], R[first[r]] = tot;
//         }
//     }

//     void remove(const int &c)
//     { // 进行remove操作
//         int i, j;
//         L[R[c]] = L[c], R[L[c]] = R[c];
//         for (i = D[c]; i != c; i = D[i])
//             for (j = R[i]; j != i; j = R[j])
//                 U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
//     }

//     void recover(const int &c)
//     { // 进行recover操作
//         int i, j;
//         for (i = U[c]; i != c; i = U[i])
//             for (j = L[i]; j != i; j = L[j])
//                 U[D[j]] = D[U[j]] = j, ++siz[col[j]];
//         L[R[c]] = R[L[c]] = c;
//     }

//     bool dance(int dep)
//     { // dance
//         int i, j, c = R[0];
//         if (!R[0])
//         {
//             for (i = 1; i < dep; ++i)
//             {
//                 int x = (stack[i] - 1) / 9 / 9 + 1;
//                 int y = (stack[i] - 1) / 9 % 9 + 1;
//                 int v = (stack[i] - 1) % 9 + 1;
//                 ans[x][y] = v;
//             }
//             return 1;
//         }
//         for (i = R[0]; i != 0; i = R[i])
//             if (siz[i] < siz[c])
//                 c = i;
//         remove(c);
//         for (i = D[c]; i != c; i = D[i])
//         {
//             stack[dep] = row[i];
//             for (j = R[i]; j != i; j = R[j])
//                 remove(col[j]);
//             if (dance(dep + 1))
//                 return 1;
//             for (j = L[i]; j != i; j = L[j])
//                 recover(col[j]);
//         }
//         recover(c);
//         return 0;
//     }
// } solver

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
    void insert(const int r, const int c)
    {
        col[++tot] = c, row[tot] = r, ++siz[c];
        D[tot] = D[c], U[D[c]] = tot;
        U[tot] = c, D[c] = tot;
        if (!first[r])
        {
            first[r] = L[tot] = R[tot] = tot;
        }
        else
        {
            L[tot] = first[r];
            R[tot] = R[first[r]];
            R[first[r]] = tot;
            L[R[first[r]]] = tot;
        }
        /// 在插入的时候要始终确保是一个环状的链表，必须完全使用该函数插入
    }
    /**
     * @brief 删除第c列
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