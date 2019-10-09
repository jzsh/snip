// 6. ZigZag Conversion
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1) return s;

        vector<string> rows(min(numRows, int(s.size())));

        int curRow = 0;
        bool goingDown = false; // 往下走

        for(char c : s) {
            rows[curRow] += c;
            // 到Z字拐点转向
            if(curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += goingDown ? 1:-1;
        }
        string ret;
        for(string row : rows)
            ret += row;
        return ret;
    }
};

int main()
{
    Solution s;
    cout << s.convert("LEETCODEISHIRING", 3) <<endl;
}
