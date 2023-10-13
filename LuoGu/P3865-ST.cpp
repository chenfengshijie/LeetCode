#include <iostream>

int n, m;
constexpr int N = 100009;
int nums[N], table[N][20];

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
void build_table()
{
    for (int i = 1; i <= n; i++)
        table[i][0] = nums[i];
    int limit = ceil(log2(n));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= limit && i + (1 << j) <= n; j++)
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        nums[i] = read();
    build_table();
}
