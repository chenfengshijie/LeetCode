#include <iostream>
#include <cstdlib>
#include <ctime>

class Treap
{
private:
    struct Node
    {
        int key, priority;
        Node *left, *right;
        Node(int k) : key(k), priority(std::rand()), left(nullptr), right(nullptr) {}
    } *root;

    void clear(Node *node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node *rotateRight(Node *node)
    {
        Node *left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }

    Node *rotateLeft(Node *node)
    {
        Node *right = node->right;
        node->right = right->left;
        right->left = node;
        return right;
    }

    Node *insert(Node *node, int key)
    {
        if (!node)
            return new Node(key);
        if (key < node->key)
        {
            node->left = insert(node->left, key);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        }
        else
        {
            node->right = insert(node->right, key);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        }
        return node;
    }

    Node *remove(Node *node, int key)
    {
        if (!node)
            return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }
            else if (!node->left || !node->right)
            {
                Node *temp = node;
                node = (node->left ? node->left : node->right);
                delete temp;
            }
            else
            {
                if (node->left->priority > node->right->priority)
                {
                    node = rotateRight(node);
                    node->right = remove(node->right, key);
                }
                else
                {
                    node = rotateLeft(node);
                    node->left = remove(node->left, key);
                }
            }
        }
        return node;
    }

public:
    Treap() : root(nullptr) { std::srand(std::time(nullptr)); }
    ~Treap() { clear(root); }

    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
};
