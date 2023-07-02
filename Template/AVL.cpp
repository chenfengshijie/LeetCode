#include <iostream>

class AVLTree
{
private:
    struct Node
    {
        int key;
        Node *left;
        Node *right;
        int height;
    };

    Node *root;

    int getHeight(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node *node)
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = std::max(leftHeight, rightHeight) + 1;
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *insertNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            Node *newNode = new Node();
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }

        if (key < root->key)
        {
            root->left = insertNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = insertNode(root->right, key);
        }
        else
        {
            return root;
        }

        updateHeight(root);

        int balanceFactor = getBalanceFactor(root);

        if (balanceFactor > 1 && key < root->left->key)
        {
            return rotateRight(root);
        }

        if (balanceFactor < -1 && key > root->right->key)
        {
            return rotateLeft(root);
        }

        if (balanceFactor > 1 && key > root->left->key)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balanceFactor < -1 && key < root->right->key)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorderTraversal(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        inorderTraversal(root->left);
        std::cout << root->key << " ";
        inorderTraversal(root->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key)
    {
        root = insertNode(root, key);
    }

    void traverseInorder()
    {
        std::cout << "Inorder Traversal: ";
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main()
{
    AVLTree avlTree;

    avlTree.insert(10);
    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(40);
    avlTree.insert(50);
    avlTree.insert(25);

    avlTree.traverseInorder();

    return 0;
}
