#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {

        int rowLen = grid.size();
        int colLen = grid[0].size();

        // 初始化第一行
        for(int c=1; c<colLen; c++) {
            grid[0][c] = grid[0][c-1] + grid[0][c];
        }

        // 初始化第一列
        for(int r=1; r<rowLen; r++) {
            grid[r][0] = grid[r-1][0] + grid[r][0];
        }

        for(int r=1; r < rowLen; r++) {
            for(int c=1; c< colLen; c++) {
                grid[r][c] = min(grid[r-1][c], grid[r][c-1]) + grid[r][c];
            }
        }

        return grid[rowLen-1][colLen-1];
    }
};

int main()
{
    Solution s;
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    int m = s.minPathSum(grid);
    cout << "min path:" <<  m << endl;
}


