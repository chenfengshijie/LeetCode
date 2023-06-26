#include <vector>
#include <string>
using std::string;
using std::vector;
// 求pattern的fail指针

vector<int> prefix_function(string s)
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
int KMP(string s, string pattern)
{
    int n = s.length(), m = pattern.length();
    auto fail = prefix_function(pattern);
    int i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        while (j > 0 && s[i] != pattern[j])
        {
            j = fail[j - 1];
        }
        if (s[i] == pattern[j])
            j++;
        if (j == m)
        {
            // 输出答案，然后退出或者继续
            return i - j + 1;
        }
    }
    return -1;
}