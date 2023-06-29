/*
 * @lc app=leetcode.cn id=164 lang=cpp
 *
 * [164] 最大间距
 */
#include <algorithm>
#include <vector>
using std::vector;
// @lc code=start
class Solution
{
public:
    int maximumGap(vector<int> &nums)
    {
        if (nums.size() < 2)
            return 0;
        if (nums.size() == 2)
            return abs(nums[1] - nums[0]);
        int min_num = *std::min_element(nums.begin(), nums.end());
        int max_num = *std::max_element(nums.begin(), nums.end());
        int n = nums.size();
        int interval = (max_num - min_num) / n + 1;
        vector<vector<int>> buckets(n + 1, vector<int>());
        for (auto &x : nums)
        {
            buckets[(x - min_num) / interval].push_back(x);
        }
        for (int i = 0; i < n; i++)
        {
            if (!buckets[i].empty())
            {
                insertionSort(buckets[i], buckets[i].size());
            }
        }
        int p = 0;
        for (int i = 0; i < n + 1; i++)
        {
            if (!buckets[i].empty())
                for (auto &x : buckets[i])
                    nums[p++] = x;
        }
        int ans = -1;
        for (int i = 0; i < n - 1; i++)
            ans = std::max(ans, nums[i + 1] - nums[i]);
        return ans;
    }

private:
    /* Function to sort an array using insertion sort*/
    void insertionSort(vector<int> &arr, int n)
    {
        int i, key, j;
        for (i = 1; i < n; i++)
        {
            key = arr[i];
            j = i - 1;

            /* Move elements of arr[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
};
// @lc code=end
int main()
{
    Solution t;
    vector<int> c1{1, 1, 1, 1};
    auto ans = t.maximumGap(c1);
    printf("%d\n", ans);
    return 0;
}