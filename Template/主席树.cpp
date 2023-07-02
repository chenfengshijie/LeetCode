#include <iostream>
#include <vector>

using namespace std;

// 定义线段树节点结构
struct Node
{
    int sum;     // 节点所代表的区间和
    Node *left;  // 左子节点
    Node *right; // 右子节点

    Node(int val) : sum(val), left(nullptr), right(nullptr) {}
};

// 构建可持久化线段树
Node *buildTree(const vector<int> &arr, int start, int end)
{
    // 叶子节点，创建新的节点并保存区间和
    if (start == end)
    {
        return new Node(arr[start]);
    }

    // 构建当前节点的左右子树
    int mid = (start + end) / 2;
    Node *left = buildTree(arr, start, mid);
    Node *right = buildTree(arr, mid + 1, end);

    // 创建新的节点并保存区间和
    Node *root = new Node(left->sum + right->sum);
    root->left = left;
    root->right = right;
    return root;
}

// 更新可持久化线段树
Node *updateTree(Node *root, int index, int value, int start, int end)
{
    // 叶子节点，创建新的节点并保存区间和
    if (start == end)
    {
        return new Node(value);
    }

    // 构建当前节点的左右子树
    int mid = (start + end) / 2;
    if (index <= mid)
    {
        Node *left = updateTree(root->left, index, value, start, mid);
        Node *right = root->right;
        // 创建新的节点并保存区间和
        root = new Node(left->sum + right->sum);
        root->left = left;
        root->right = right;
    }
    else
    {
        Node *left = root->left;
        Node *right = updateTree(root->right, index, value, mid + 1, end);
        // 创建新的节点并保存区间和
        root = new Node(left->sum + right->sum);
        root->left = left;
        root->right = right;
    }

    return root;
}

// 查询可持久化线段树的区间和
int queryTree(Node *root, int left, int right, int start, int end)
{
    // 查询区间完全包含当前节点所代表的区间，直接返回节点的区间和
    if (left <= start && right >= end)
    {
        return root->sum;
    }

    // 查询区间与当前节点所代表的区间无交集，返回0
    if (left > end || right < start)
    {
        return 0;
    }

    // 查询左右子树
    int mid = (start + end) / 2;
    int leftSum = queryTree(root->left, left, right, start, mid);
    int rightSum = queryTree(root->right, left, right, mid + 1, end);

    return leftSum + rightSum;
}

int main()
{
    vector<int> arr = {1, 3, 5, 7, 9};
    vector<Node *> roots; // 保存每个版本的根节点

    // 构建初始版本的线段树并保存根节点
    Node *root = buildTree(arr, 0, arr.size() - 1);
    roots.push_back(root);

    // 更新线段树的第二个元素为2，并保存根节点
    root = updateTree(root, 1, 2, 0, arr.size() - 1);
    roots.push_back(root);

    // 查询第一次版本的线段树中第二到第四个元素的区间和
    int sum = queryTree(roots[0], 1, 3, 0, arr.size() - 1);
    cout << "第一次版本的区间和：" << sum << endl;

    return 0;
}
