#include <string>
#include <iostream>
#include <vector>

using namespace std;

// 中心拓展法
class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size() < 1) return "";
        int i = 0;
        int start = 0;
        int end = 0;
        for(i = 0; i < s.size(); i++) {
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i+1); // 回文的中心在字母中间

            int len = max(len1, len2);
            if(len > end - start) {
                start = i - (len - 1)/2; // 回文长度为奇数或偶数
                end = i + len/2;
            }
        }
        return s.substr(start, (end-start+1));
    }

    int expandAroundCenter(string s, int left, int right) {
        while(left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right -left - 1;  // left,right为不相等的字符
    }

    string longestPalindrome_dp(string s);
};

// 动态规划
// 初始状态：
//
// dp[i][i]=1; //单个字符是回文串
// dp[i][i+1]=1 if s[i]=s[i+1]; //连续两个相同字符是回文串

string Solution::longestPalindrome_dp(string s)
{
    int len = s.size();
    if(len == 0 || len == 1)
        return s;

    int max = 1;
    int start = 0;
    // 初始化动态数组
    vector<vector<int>> dp(len, vector<int>(len));
    for(int i=0; i<len; i++) {
        dp[i][i] = 1;
        if(i<len-1 && s[i] == s[i+1]) {
            dp[i][i+1] = 1;
            max = 2;
            start = i;
        }
    }

    for(int l=3; l<=len;l++) // l表示检索的子串长度
    {
        for(int i=0; i+l-1<len; i++)
        {
            int j = i+l-1; // 终止字符的位置
            if(s[i]==s[j] && dp[i+1][j-1] == 1) {
                dp[i][j] = 1;
                start = i;
                max = l;
            }
        }
    }
    return s.substr(start, max);
}



int main()
{
    Solution s;
    cout << s.longestPalindrome("abcb") << endl;
    cout << s.longestPalindrome("abb") << endl;
    cout << s.longestPalindrome_dp("abcb") << endl;
    cout << s.longestPalindrome_dp("abb") << endl;
}
