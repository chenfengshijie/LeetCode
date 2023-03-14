/*
 * @lc app=leetcode.cn id=114 lang=cpp
 *
 * [114] 二叉树展开为链表
 */
#include <vector>
using std::vector;
// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// @lc code=start

class Solution
{
public:
    void flatten(TreeNode *root)
    {
        if (root == nullptr)
            return;
        DFS(root);
        return;
    }
    TreeNode *DFS(TreeNode *p)
    {
        if (p->left != nullptr && p->right != nullptr)
        {
            auto tmp = p->right;
            p->right = p->left;
            auto cnt = DFS(p->left);
            cnt->right = tmp;
            p->left = nullptr;
            return DFS(tmp);
        }
        if (p->left != nullptr)
        {
            p->right = p->left;
            auto tmp = p->left;
            p->left = nullptr;
            return DFS(tmp);
        }
        if (p->right != nullptr)
        {
            return DFS(p->right);
        }
        return p;
    }
};
// @lc code=end
int main()
{
    vector<TreeNode *> p(9);
    for (int i = 1; i < 7; i++)
    {
        p[i] = new TreeNode(i);
    }
    p[1]->left = p[2], p[1]->right = p[5];
    p[2]->left = p[3], p[2]->right = p[4];
    p[5]->right = p[6];
    Solution t;
    t.flatten(p[1]);
    return 0;
}
