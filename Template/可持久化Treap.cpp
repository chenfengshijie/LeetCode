#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 节点结构
struct Node
{
    int key;      // 键值
    int priority; // 优先级
    int size;     // 子树大小
    Node *left;   // 左子节点指针
    Node *right;  // 右子节点指针

    Node(int k)
    {
        key = k;
        priority = rand(); // 生成随机优先级
        size = 1;
        left = nullptr;
        right = nullptr;
    }
};

class PersistentTreap
{
private:
    Node *root;

    // 获取节点的大小（子树大小）
    int getSize(Node *node)
    {
        return (node != nullptr) ? node->size : 0;
    }

    // 更新节点的大小
    void updateSize(Node *node)
    {
        if (node != nullptr)
        {
            node->size = getSize(node->left) + getSize(node->right) + 1;
        }
    }

    // 分割树为两个子树
    void split(Node *root, int key, Node *&left, Node *&right)
    {
        if (root == nullptr)
        {
            left = nullptr;
            right = nullptr;
        }
        else if (root->key <= key)
        {
            split(root->right, key, root->right, right);
            left = root;
        }
        else
        {
            split(root->left, key, left, root->left);
            right = root;
        }
        updateSize(root);
    }

    // 合并两个子树
    Node *merge(Node *left, Node *right)
    {
        if (left == nullptr)
        {
            return right;
        }
        if (right == nullptr)
        {
            return left;
        }
        if (left->priority > right->priority)
        {
            left->right = merge(left->right, right);
            updateSize(left);
            return left;
        }
        else
        {
            right->left = merge(left, right->left);
            updateSize(right);
            return right;
        }
    }

    // 插入节点
    Node *insert(Node *root, Node *node)
    {
        if (root == nullptr)
        {
            return node;
        }
        if (node->priority > root->priority)
        {
            split(root, node->key, node->left, node->right);
            updateSize(node);
            return node;
        }
        if (node->key < root->key)
        {
            root->left = insert(root->left, node);
        }
        else
        {
            root->right = insert(root->right, node);
        }
        updateSize(root);
        return root;
    }

    // 删除节点
    Node *erase(Node *root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->key == key)
        {
            Node *temp = merge(root->left, root->right);
            delete root;
            return temp;
        }
        if (key < root->key)
        {
            root->left = erase(root->left, key);
        }
        else
        {
            root->right = erase(root->right, key);
        }
        updateSize(root);
        return root;
    }

    // 查询节点
    Node *search(Node *root, int key)
    {
        if (root == nullptr || root->key == key)
        {
            return root;
        }
        if (key < root->key)
        {
            return search(root->left, key);
        }
        else
        {
            return search(root->right, key);
        }
    }

    // 查找前驱节点
    Node *predecessor(Node *root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->key < key)
        {
            Node *pred = predecessor(root->right, key);
            return (pred != nullptr) ? pred : root;
        }
        else
        {
            return predecessor(root->left, key);
        }
    }

    // 查找后驱节点
    Node *successor(Node *root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->key > key)
        {
            Node *succ = successor(root->left, key);
            return (succ != nullptr) ? succ : root;
        }
        else
        {
            return successor(root->right, key);
        }
    }

public:
    PersistentTreap()
    {
        root = nullptr;
    }

    // 插入节点
    void insert(int key)
    {
        root = insert(root, new Node(key));
    }

    // 删除节点
    void erase(int key)
    {
        root = erase(root, key);
    }

    // 查询节点
    Node *search(int key)
    {
        return search(root, key);
    }

    // 查询前驱节点
    Node *getPredecessor(int key)
    {
        return predecessor(root, key);
    }

    // 查询后驱节点
    Node *getSuccessor(int key)
    {
        return successor(root, key);
    }

    // 打印树中的节点
    void printTree(Node *root)
    {
        if (root != nullptr)
        {
            printTree(root->left);
            cout << "Key: " << root->key << ", Priority: " << root->priority << endl;
            printTree(root->right);
        }
    }

    void printTree()
    {
        cout << "Current Tree:" << endl;
        printTree(root);
    }
};

int main()
{
    srand(time(nullptr));

    PersistentTreap treap;

    // 插入节点
    treap.insert(5);
    treap.insert(3);
    treap.insert(7);
    treap.insert(1);
    treap.insert(4);

    // 打印当前树
    treap.printTree();

    // 查询节点
    Node *searchNode = treap.search(3);
    if (searchNode != nullptr)
    {
        cout << "Node found: Key = " << searchNode->key << ", Priority = " << searchNode->priority << endl;
    }
    else
    {
        cout << "Node not found." << endl;
    }

    // 查询前驱节点
    Node *predecessor = treap.getPredecessor(5);
    if (predecessor != nullptr)
    {
        cout << "Predecessor found: Key = " << predecessor->key << ", Priority = " << predecessor->priority << endl;
    }
    else
    {
        cout << "Predecessor not found." << endl;
    }

    // 查询后驱节点
    Node *successor = treap.getSuccessor(5);
    if (successor != nullptr)
    {
        cout << "Successor found: Key = " << successor->key << ", Priority = " << successor->priority << endl;
    }
    else
    {
        cout << "Successor not found." << endl;
    }

    // 删除节点
    treap.erase(3);

    // 打印修改后的树
    treap.printTree();

    return 0;
}
