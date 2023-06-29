/*
 * @lc app=leetcode.cn id=140 lang=cpp
 *
 * [140] 单词拆分 II
 */
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;
// @lc code=start
class Solution
{
public:
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        memset(is_end, 0, sizeof(is_end));
        memset(nex, 0, sizeof(nex));
        for (int i = 0; i < wordDict.size(); i++)
            add_word(wordDict[i], i);
        DFS(0, 0, s.length(), s, wordDict);
        return answers;
    }

private:
    int is_end[10000];
    int nex[10000][26];
    int cnt = 0;
    string ans;
    vector<string> answers;
    void add_word(const string s, const int ps)
    {
        int p = 0;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            if (nex[p][s[i] - 'a'] == 0)
            {
                ++cnt;
                nex[p][s[i] - 'a'] = cnt;
                p = cnt;
            }
            else
                p = nex[p][s[i] - 'a'];
            if (i == n - 1)
                is_end[p] = ps;
        }
        return;
    }
    void DFS(int ps, int pt, const int lens, const string s, const vector<string> &WordDict)
    {
        if (ps == lens)
        {
            answers.push_back(ans);
            return;
        }
        while (nex[pt][s[ps] - 'a'] != 0)
        {
            ps++;
            pt = nex[pt][s[ps] - 'a'];
            if (is_end[pt] != 0)
            {
                auto tmp = ans;
                ans = ans.empty() ? ans + WordDict[is_end[pt]] : ans + " " + WordDict[is_end[pt]];
                DFS(ps, 0, lens, s, WordDict);
                ans = tmp;
            }
        }
        return;
    }
};
// @lc code=end
Solution t;
int main()
{
    vector<string> cc{"cat", "cats", "and", "sand", "dog"};

    auto ans = t.wordBreak("catsanddog", cc);
    auto lambda = [](string s)
    { std::cout << s << std::endl; };
    std::for_each(ans.begin(), ans.end(), lambda);
    return 0;
}