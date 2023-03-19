#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
using std::vector;
class Solution
{
public:
    int beautifulSubsets(vector<int> &nums, int k)
    {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        vector<int> res(n, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
                if (nums[j] - nums[i] == k)
                    res[i] = res[i] | (1 << j);
        }
        int S = (1 << n);
        int ans = 0;
        for (int i = 1; i < S; i++)
        {
            if (check(i, res, n))
                ++ans;
        }
        return ans;
    }

private:
    bool check(int S, vector<int> &res, int n)
    {
        for (int i = 0; i < n; i++)
        {
            if (S & (1 << i))
                if (S & res[i])
                    return false;
        }
        return true;
    }
};
int main()
{
}