#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

const int CHAR_SIZE = 256; // 字符集大小

// 构建坏字符规则
void buildBadCharRule(const std::string &pattern, std::vector<int> &badCharRule)
{
    int m = pattern.length();
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        badCharRule[i] = -1; // 初始化为-1表示该字符在模式串中未出现过
    }
    for (int i = 0; i < m; i++)
    {
        badCharRule[pattern[i]] = i; // 记录字符最后出现的位置
    }
}

// 构建好后缀规则 - 预处理后缀数组
void buildSuffixArray(const std::string &pattern, std::vector<int> &suffixArray, std::vector<bool> &prefix)
{
    int m = pattern.length();
    suffixArray.resize(m);
    prefix.resize(m);
    std::fill(prefix.begin(), prefix.end(), false);

    int lastPrefixPos = m - 1;
    for (int i = m - 2; i >= 0; i--)
    {
        if (pattern[i] == pattern[lastPrefixPos])
        {
            suffixArray[i] = lastPrefixPos;
            lastPrefixPos--;
        }
        else
        {
            suffixArray[i] = lastPrefixPos;
        }
    }

    for (int i = 0; i < m - 1; i++)
    {
        int len = 0;
        int j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - len])
        {
            prefix[len] = (j == 0);
            len++;
            j--;
        }
        if (j == -1)
        {
            suffixArray[m - 1 - len] = 0;
        }
    }
}

// BM算法匹配函数
void BM(const std::string &text, const std::string &pattern)
{
    int n = text.length();
    int m = pattern.length();

    std::vector<int> badCharRule(CHAR_SIZE); // 坏字符规则
    std::vector<int> suffixArray;            // 好后缀规则 - 后缀数组
    std::vector<bool> prefix;                // 好后缀规则 - 前缀数组

    buildBadCharRule(pattern, badCharRule);
    buildSuffixArray(pattern, suffixArray, prefix);

    int i = 0; // i为主串当前比较位置
    while (i <= n - m)
    {
        int j = m - 1; // j为模式串当前比较位置

        // 从模式串末尾开始比较
        while (j >= 0 && pattern[j] == text[i + j])
        {
            j--;
        }

        if (j < 0)
        {
            // 匹配成功
            std::cout << "Pattern occurs at index " << i << std::endl;
            i += (i + m < n) ? m - badCharRule[text[i + m]] : 1;
        }
        else
        {
            // 坏字符规则和好后缀规则选择较大的跳过步数
            int badCharSkip = j - badCharRule[text[i + j]];
            int goodSuffixSkip = 0;
            if (j < m - 1)
            {
                goodSuffixSkip = suffixArray[j + 1];
                if (j > 0)
                {
                    goodSuffixSkip = std::max(goodSuffixSkip, j - suffixArray[j] + 1);
                }
            }
            i += std::max(badCharSkip, goodSuffixSkip);
        }
    }
}

int main()
{
    std::string text = "ABCABABCDABABCD";
    std::string pattern = "ABABCD";

    BM(text, pattern);

    return 0;
}
