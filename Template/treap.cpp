#include <iostream>
#include <cstdlib>

using namespace std;

///! 基于旋转的Treap实现

// 定义Treap节点结构
struct Node
{
    int key;      // 键
    int priority; // 优先级
    Node *left;   // 左子节点指针
    Node *right;  // 右子节点指针

    Node(int k)
    {
        key = k;
        priority = rand(); // 随机生成优先级
        left = right = nullptr;
    }
};

class Treap
{
public:
    // 构造函数
    Treap()
    {
        root = nullptr;
    }

    // 插入节点到Treap中
    void insert(int key)
    {
        root = insertNode(root, key);
    }

    // 删除节点
    void remove(int key)
    {
        root = removeNode(root, key);
    }

    // 中序遍历Treap
    void inorderTraversal()
    {
        inorder(root);
    }

private:
    Node *root; // 根节点指针

    // 右旋操作
    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        // 执行右旋操作
        x->right = y;
        y->left = T2;

        return x; // 返回新的根节点
    }

    // 左旋操作
    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // 执行左旋操作
        y->left = x;
        x->right = T2;

        return y; // 返回新的根节点
    }

    // 插入节点到Treap中
    Node *insertNode(Node *root, int key)
    {
        // 如果树为空，创建一个新节点作为根节点
        if (root == nullptr)
        {
            return new Node(key);
        }

        // 如果插入的键小于当前节点的键，向左子树插入
        if (key < root->key)
        {
            root->left = insertNode(root->left, key);

            // 如果左子节点的优先级大于当前节点的优先级，执行右旋操作
            if (root->left->priority > root->priority)
            {
                root = rotateRight(root);
            }
        }
        // 如果插入的键大于等于当前节点的键，向右子树插入
        else
        {
            root->right = insertNode(root->right, key);

            // 如果右子节点的优先级大于当前节点的优先级，执行左旋操作
            if (root->right->priority > root->priority)
            {
                root = rotateLeft(root);
            }
        }

        return root;
    }

    // 删除节点
    Node *removeNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }

        // 如果要删除的键小于当前节点的键，向左子树删除
        if (key < root->key)
        {
            root->left = removeNode(root->left, key);
        }
        // 如果要删除的键大于当前节点的键，向右子树删除
        else if (key > root->key)
        {
            root->right = removeNode(root->right, key);
        }
        // 找到要删除的节点
        else
        {
            // 节点没有左子树
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                root = temp;
            }
            // 节点没有右子树
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                root = temp;
            }
            // 节点有左右子树
            else
            {
                // 根据优先级比较，选择左旋或右旋
                if (root->left->priority < root->right->priority)
                {
                    root = rotateLeft(root);
                    root->left = removeNode(root->left, key);
                }
                else
                {
                    root = rotateRight(root);
                    root->right = removeNode(root->right, key);
                }
            }
        }

        return root;
    }

    // 中序遍历Treap
    void inorder(Node *root)
    {
        if (root != nullptr)
        {
            inorder(root->left);
            cout << "Key: " << root->key << " Priority: " << root->priority << endl;
            inorder(root->right);
        }
    }
};

int main()
{
    Treap treap;

    // 插入节点到Treap中
    treap.insert(50);
    treap.insert(30);
    treap.insert(20);
    treap.insert(40);
    treap.insert(70);
    treap.insert(60);
    treap.insert(80);

    // 中序遍历Treap并输出键和优先级
    cout << "Treap after insertion:" << endl;
    treap.inorderTraversal();

    // 删除节点
    treap.remove(30);
    treap.remove(40);

    // 中序遍历Treap并输出键和优先级
    cout << "Treap after removal:" << endl;
    treap.inorderTraversal();

    return 0;
}
