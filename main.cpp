#include <iostream>
#include <vector>
#include <algorithm>
class BIT2
{
public:
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

int main()
{
    std::vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7};
    BIT2 bit(arr.size() + 10);
    for (int i = 1; i < arr.size(); i++)
    {
        bit.add(i, arr[i] - arr[i - 1]);
    }
    std::cout << bit.sum(3) << std::endl;
    return 0;
}