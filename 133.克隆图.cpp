/*
 * @lc app=leetcode.cn id=133 lang=cpp
 *
 * [133] 克隆图
 */

// @lc code=start
/*
// Definition for a Node.*/
#include <vector>
#include <queue>
#include <unordered_map>
using std::vector;
class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};
struct Cmp
{
    size_t operator()(const Node ls)
    {
        return ls.val;
    }
};
class Solution
{
public:
    Node *DFS_clone(Node *node)
    {
        Node *nnode = new Node(node->val);
        for (auto &neighbor : node->neighbors)
        {
            if (old2new.find(neighbor) == old2new.end())
            {
                Node *new_node = DFS_clone(neighbor);
                nnode->neighbors.push_back(new_node);
            }
            else
            {
                nnode->neighbors.push_back(old2new[neighbor]);
            }
        }
        return nnode;
    }

    Node *cloneGraph(Node *node)
    {
        return DFS_clone(node);
    }

private:
    std::unordered_map<Node *, Node *, Cmp> old2new;
};
// @lc code=end

int main()
{
    Solution t;
    Node a(12);
    t.cloneGraph(&a);
    return 0;
}