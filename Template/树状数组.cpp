#include <cstdio>
#include <vector>
#include <algorithm>
/// 单点修改，区间求和|| 区间修改，单点求值都可以使用差分数组解决

class BIT
{
public:
    static const int MAXN = 100000;
    std::vector<int> nums; // 原数组
    std::vector<int> d;    // 差分数组
    int n;                 // 数组大小
    BIT(int n) : n(n)
    {
        nums.resize(n + 1);
        d.resize(n + 1);
    }
    inline int lowbit(int x)
    {
        return x & (-x);
    }
    void add(int k, int x)
    {
        for (int i = k; i <= n; i += lowbit(i))
            d[i] += x;
        return;
    }
    int sum(int k)
    {
        int ans = 0;
        for (int i = k; i > 0; i -= lowbit(i))
            ans += d[i];
        return ans;
    }
};

///! 区间修改，区间求值

class BIT2
{
    static const int MAXN = 100000;
    std::vector<int> nums; // 原数组
    std::vector<int> d1;   // 差分数组1,用于维护原数组的差分
    std::vector<int> d2;   // 差分数组2，用于维护d[i] * i.
    int n;                 // 数组大小
    BIT2(int n) : n(n)
    {
        d1.resize(n + 1);
        d2.resize(n + 1);
    }
    inline int lowbit(int x)
    {
        return x & (-x);
    }
    void add(int k, int x)
    {
        int v1 = k * x;
        for (int i = k; i <= n; i += lowbit(i))
        {
            d1[i] += x;
            d2[i] += v1;
        }
        return;
    }
    int sum(std::vector<int> &d, int k)
    {
        int ans = 0;
        for (int i = k; i > 0; i -= lowbit(i))
            ans += d[i];
        return ans;
    }
    int sum(int k)
    {
        return sum(d1, k) * (k + 1) - sum(d2, k);
    }
};

///! 二维树状数组

/// @brief 二维树状数组,单点修改，区间求和; 区间修改，单点求值类似（求差分，差分的定义为
/// d[i][j] = nums[i][j] - nums[i - 1][j] - nums[i][j - 1] + nums[i - 1][j - 1]）
class BIT2D
{
public:
    int n, m;
    std::vector<std::vector<int>> d;
    std::vector<std::vector<int>> nums;

    BIT2D(int n, int m) : n(n), m(m)
    {
        d.resize(n + 1);
        nums.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            d[i].resize(m + 1);
            nums[i].resize(m + 1);
        }
    }
    inline int lowbit(int x)
    {
        return x & (-x);
    }
    void add(int x, int y, int k)
    {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                d[i][j] += k;
        return;
    }
    int sum(int x, int y)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            for (int j = y; j > 0; j -= lowbit(j))
                ans += d[i][j];
        return ans;
    }
    void modify(int x, int y, int k)
    {
        add(x, y, k - nums[x][y]);
        add(x + 1, y, -k + nums[x][y]);
        add(x, y + 1, -k + nums[x][y]);
        add(x + 1, y + 1, k - nums[x][y]);
        nums[x][y] = k;
        return;
    }
};

///! 二维树状数组，区间修改，区间求值
class BIT2D2
{
    int n, m;
    std::vector<std::vector<int>> d1;
    std::vector<std::vector<int>> d2;
    std::vector<std::vector<int>> d3;
    std::vector<std::vector<int>> d4;
    std::vector<std::vector<int>> nums;
    inline int lowbit(int x)
    {
        return x & (-x);
    }
    void add(int x, int y, int k)
    {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
            {
                d1[i][j] += k;
                d2[i][j] += k * x;
                d3[i][j] += k * y;
                d4[i][j] += k * x * y;
            }
        return;
    }
    int sum(std::vector<std::vector<int>> &d, int x, int y)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            for (int j = y; j > 0; j -= lowbit(j))
                ans += d[i][j];
        return ans;
    }
    void range_add(int x1, int y1, int x2, int y2, int z)
    {
        add(x1, y1, z);
        add(x1, y2 + 1, -z);
        add(x2 + 1, y1, -z);
        add(x2 + 1, y2 + 1, z);
    }
};