#include <iostream>

template <typename T>
struct LeftistNode
{
    T value;                // 节点的值
    int dist;               // 节点的零路径长
    LeftistNode<T> *left;   // 左子树的指针
    LeftistNode<T> *right;  // 右子树的指针
    LeftistNode<T> *father; // 父节点的指针

    // 构造函数
    LeftistNode(const T &val)
        : value(val), dist(0), left(nullptr), right(nullptr), father(nullptr) {}
};

template <typename T>
class LeftistTree
{
public:
    LeftistTree() : root(nullptr) {}

    // 合并两个左偏树
    void merge(LeftistTree<T> &other)
    {
        root = mergeNodes(root, other.root);
    }

    // 插入一个元素
    LeftistNode<T> *insert(const T &value)
    {
        LeftistNode<T> *newNode = new LeftistNode<T>(value);
        root = mergeNodes(root, newNode);
        return newNode;
    }

    // 删除最大值
    void pop()
    {
        if (root == nullptr)
        {
            return; // 左偏树为空
        }

        LeftistNode<T> *oldRoot = root;
        root = mergeNodes(root->left, root->right);
        if (root != nullptr)
        {
            root->father = nullptr; // 更新根节点的父节点指针
        }
        delete oldRoot;
    }

    // 删除任意节点
    void remove(LeftistNode<T> *node)
    {
        if (node == nullptr)
        {
            return; // 节点为空
        }

        if (node == root)
        {
            pop(); // 删除根节点
            return;
        }

        LeftistNode<T> *parent = node->father; // 获取父节点

        // 重新连接子树
        if (parent->left == node)
        {
            parent->left = mergeNodes(node->left, node->right);
        }
        else
        {
            parent->right = mergeNodes(node->left, node->right);
        }

        if (parent->left != nullptr)
        {
            parent->left->father = parent; // 更新左子树的父节点指针
        }
        if (parent->right != nullptr)
        {
            parent->right->father = parent; // 更新右子树的父节点指针
        }

        delete node;
        maintainHeapProperty(parent); // 维护左偏树性质
    }

    // 获取最大值
    T top() const
    {
        if (root == nullptr)
        {
            throw std::runtime_error("Leftist Tree is empty.");
        }
        return root->value;
    }

private:
    LeftistNode<T> *root;

    // 合并两个节点
    LeftistNode<T> *mergeNodes(LeftistNode<T> *node1, LeftistNode<T> *node2)
    {
        if (node1 == nullptr)
        {
            return node2;
        }
        if (node2 == nullptr)
        {
            return node1;
        }

        if (node1->value < node2->value)
        {
            std::swap(node1, node2);
        }

        node1->right = mergeNodes(node1->right, node2);
        if (node1->left == nullptr || node1->left->dist < node1->right->dist)
        {
            std::swap(node1->left, node1->right);
        }
        node1->dist = (node1->right == nullptr) ? 0 : node1->right->dist + 1;

        if (node1->left != nullptr)
        {
            node1->left->father = node1; // 更新左子树的父节点指针
        }
        if (node1->right != nullptr)
        {
            node1->right->father = node1; // 更新右子树的父节点指针
        }

        return node1;
    }

    // 维护左偏树的性质
    void maintainHeapProperty(LeftistNode<T> *node)
    {
        while (node != nullptr)
        {
            int distLeft = (node->left == nullptr) ? -1 : node->left->dist;
            int distRight = (node->right == nullptr) ? -1 : node->right->dist;
            int newDist = std::min(distLeft, distRight) + 1;

            if (newDist < node->dist)
            {
                node->dist = newDist;
                if (distLeft < distRight)
                {
                    std::swap(node->left, node->right);
                }
                node = node->father;
            }
            else
            {
                break;
            }
        }
    }
};

int main()
{
    LeftistTree<int> tree;
    tree.insert(1);
    auto s1 = tree.insert(2);
    tree.insert(3);
    printf("%d ", tree.top());
    tree.pop();
    tree.remove(s1);
    printf("%d ", tree.top());
    return 0;
}