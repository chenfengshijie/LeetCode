#include <iostream>
#include <queue>
#include <unordered_map>

// Trie树节点
struct TrieNode
{
    std::unordered_map<char, TrieNode *> children;
    TrieNode *parent;
    TrieNode *fail; // 失败指针
    bool isWordEnd;
    int patternIndex; // 模式串索引

    TrieNode()
    {
        parent = nullptr;
        fail = nullptr;
        isWordEnd = false;
        patternIndex = -1;
    }
};

// 构建Trie树
void buildTrie(const std::vector<std::string> &patterns, TrieNode *root)
{
    for (int i = 0; i < patterns.size(); ++i)
    {
        const std::string &pattern = patterns[i];
        TrieNode *curr = root;
        for (char c : pattern)
        {
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = new TrieNode();
                curr->children[c]->parent = curr;
            }
            curr = curr->children[c];
        }
        curr->isWordEnd = true;
        curr->patternIndex = i;
    }
}

// 构建失败指针
void buildFailurePointer(TrieNode *root)
{
    std::queue<TrieNode *> q;
    // 根节点的失败指针为空
    root->fail = root;
    // 将根节点的子节点加入队列
    for (const auto &pair : root->children)
    {
        TrieNode *child = pair.second;
        child->fail = root;
        q.push(child);
    }

    // 使用BFS构建失败指针
    while (!q.empty())
    {
        TrieNode *curr = q.front();
        q.pop();

        for (const auto &pair : curr->children)
        {
            char c = pair.first;
            TrieNode *child = pair.second;

            TrieNode *failNode = curr->fail;
            while (failNode != root && failNode->children.find(c) == failNode->children.end())
            {
                failNode = failNode->fail;
            }

            if (failNode->children.find(c) != failNode->children.end())
            {
                child->fail = failNode->children[c];
            }
            else
            {
                child->fail = root;
            }

            q.push(child);
        }
    }
}

// AC自动机匹配函数
void ACMatch(const std::string &text, const std::vector<std::string> &patterns)
{
    TrieNode *root = new TrieNode();
    buildTrie(patterns, root);
    buildFailurePointer(root);

    TrieNode *curr = root; // 当前节点

    for (int i = 0; i < text.length(); ++i)
    {
        char c = text[i];

        // 根据当前字符和当前节点进行匹配
        while (curr != root && curr->children.find(c) == curr->children.end())
        {
            curr = curr->fail;
        }

        if (curr->children.find(c) != curr->children.end())
        {
            curr = curr->children[c]; // 匹配成功，跳转到下一个节点

            // 输出匹配的模式串
            TrieNode *matchNode = curr;
            while (matchNode != root)
            {
                if (matchNode->isWordEnd)
                {
                    int patternIndex = matchNode->patternIndex;
                    std::cout << "Pattern \"" << patterns[patternIndex] << "\" occurs at index " << i - patterns[patternIndex].length() + 1 << std::endl;
                }
                matchNode = matchNode->fail;
            }
        }
    }

    // 释放内存
    std::queue<TrieNode *> q;
    q.push(root);
    while (!q.empty())
    {
        TrieNode *node = q.front();
        q.pop();
        for (const auto &pair : node->children)
        {
            q.push(pair.second);
        }
        delete node;
    }
}

int main()
{
}
