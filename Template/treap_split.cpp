#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
class Treap
{
private:
    struct TreapNode
    {
        int key, priority;
        TreapNode *left, *right;
        TreapNode(int k) : key(k), priority(std::rand()), left(nullptr), right(nullptr) {}
    };
    std::pair<TreapNode *, TreapNode *> split(TreapNode *node, const int key)
    {
        if (!node)
            return std::make_pair(nullptr, nullptr);
        if (key < node->key)
        {
            std::pair<TreapNode *, TreapNode *> p = split(node->left, key);
            node->left = p.second;
            return std::make_pair(p.first, node);
        }
        else
        {
            std::pair<TreapNode *, TreapNode *> p = split(node->right, key);
            node->right = p.first;
            return std::make_pair(node, p.second);
        }
    }

    TreapNode *merge(TreapNode *left, TreapNode *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;
        if (left->priority > right->priority)
        {
            left->right = merge(left->right, right);
            return left;
        }
        else
        {
            right->left = merge(left, right->left);
            return right;
        }
    }

public:
    TreapNode *root;
    void insert(TreapNode *&node, int key)
    {
        std::pair<TreapNode *, TreapNode *> p = split(node, key);
        node = merge(merge(p.first, new TreapNode(key)), p.second);
    }
    void remove(TreapNode *&node, int key)
    {
        std::pair<TreapNode *, TreapNode *> p = split(node, key);
        std::pair<TreapNode *, TreapNode *> q = split(p.first, key - 1);
        delete q.second;
        node = merge(q.first, p.second);
    }
};