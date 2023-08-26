/*
 * @lc app=leetcode.cn id=2569 lang=cpp
 *
 * [2569] 更新数组后处理求和查询
 */
#include <iostream>
#include <vector>
#include <numeric>
using std::vector;
// @lc code=start
class SegTree
{
public:
    struct Node
    {
        int l, r, sum;
        bool lazyTag;
        Node(int ls, int rs) : l(ls), r(rs), sum(0), lazyTag(false) {}
        Node() : l(0), r(0), sum(0), lazyTag(false) {}
    };
    SegTree(int n)
    {
        tree.resize(n << 2);
    }
    vector<Node> tree;
    void build(int p, int l, int r, vector<int> &nums)
    {
        tree[p] = Node(l, r);
        if (l == r)
        {
            tree[p].sum = nums[l];
            return;
        }
        int mid = (l + r) / 2;
        int lson = p << 1;
        int rson = (p << 1) | 1;
        build(lson, l, mid, nums);
        build(rson, mid + 1, r, nums);
        tree[p].sum = tree[lson].sum + tree[rson].sum;
    }
    void push_down(int p)
    {
        if (tree[p].lazyTag && tree[p].l != tree[p].r)
        {
            int lson = p << 1;
            int rson = (p << 1) | 1;
            tree[lson].sum = (tree[lson].r - tree[lson].l + 1) - tree[lson].sum;
            tree[rson].sum = (tree[rson].r - tree[rson].l + 1) - tree[rson].sum;
            tree[lson].lazyTag = !tree[lson].lazyTag;
            tree[rson].lazyTag = !tree[rson].lazyTag;
            tree[p].lazyTag = false;
        }
        return;
    }
    int get_sum(int p, int l, int r)
    {
        int ans = 0;
        if (tree[p].l >= l && tree[p].r <= r)
        {
            return tree[p].sum;
        }
        push_down(p);
        int mid = (tree[p].l + tree[p].r) >> 1;
        int lson = p << 1, rson = (p << 1) | 1;
        if (l <= mid)
        {
            ans += get_sum(lson, l, r);
        }
        if (r > mid)
        {
            ans += get_sum(rson, l, r);
        }
        return ans;
    }
    void modify(int p, int l, int r)
    {
        push_down(p);
        if (tree[p].l >= l && tree[p].r <= r)
        {
            tree[p].sum = (tree[p].r - tree[p].l + 1) - tree[p].sum;
            tree[p].lazyTag = !tree[p].lazyTag;
            return;
        }

        int mid = (tree[p].l + tree[p].r) >> 1;
        int lson = p << 1, rson = (p << 1) | 1;
        if (l <= mid)
        {
            modify(lson, l, r);
        }
        if (r > mid)
        {
            modify(rson, l, r);
        }
        tree[p].sum = tree[lson].sum + tree[rson].sum;
    }
};
class Solution
{
public:
    vector<long long> handleQuery(vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &queries)
    {
        SegTree segTree(nums1.size());
        segTree.build(1, 0, nums1.size() - 1, nums1);
        int n = nums1.size() - 1;
        vector<long long> ans;
        long long sum = std::accumulate(nums2.begin(), nums2.end(), 0ll);
        for (auto &query : queries)
        {
            if (query[0] == 1)
            {
                segTree.modify(1, query[1], query[2]);
            }
            else if (query[0] == 2)
                sum += segTree.get_sum(1, 0, n) * query[1];
            else
                ans.push_back(sum);
        }
        return ans;
    }
};
// @lc code=end
int main()
{
    vector<int> nums1 = {0, 1, 0, 0, 0, 0};
    vector<int> nums2 = {14, 4, 13, 13, 47, 18};
    vector<vector<int>> queries = {{3, 0, 0}, {1, 4, 4}, {1, 1, 4}, {1, 3, 4}, {3, 0, 0}, {2, 5, 0}, {1, 1, 3}, {2, 16, 0}, {2, 10, 0}, {3, 0, 0}, {3, 0, 0}, {2, 6, 0}};

    Solution sol;
    auto ans = sol.handleQuery(nums1, nums2, queries);
    for (auto &i : ans)
    {
        std::cout << i << " ";
    }
    return 0;
}