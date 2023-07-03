#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
class PersistentTreap
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
        else
        {
            TreapNode *newNode = new TreapNode(node->key);
            newNode->priority = node->priority;
            newNode->left = node->left;
            newNode->right = node->right;
            if (key < node->key)
            {
                std::pair<TreapNode *, TreapNode *> p = split(newNode->left, key);
                newNode->left = p.second;
                return std::make_pair(p.first, newNode);
            }
            else
            {
                std::pair<TreapNode *, TreapNode *> p = split(newNode->right, key);
                newNode->right = p.first;
                return std::make_pair(newNode, p.second);
            }
        }
    }
    TreapNode *merge(TreapNode *u, TreapNode *v)
    {
        if (!u)
            return v;
        if (!v)
            return u;
        if (u->priority > u->priority)
        {
            TreapNode *newNode = new TreapNode(u->key);
            newNode->priority = u->priority;
            newNode->left = u->left;
            newNode->right = merge(u->right, v);
            // 后续需要更新其他的数据在此使用update函数
            return newNode;
        }
        else
        {
            TreapNode *newNode = new TreapNode(v->key);
            newNode->priority = v->priority;
            newNode->right = v->right;
            newNode->left = merge(u, v->left);
            // 后续需要更新其他的数据在此使用update函数
            return newNode;
        }
    }

public:
    std::vector<TreapNode *> root;
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