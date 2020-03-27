// 746. Min Cost Climbing Stairs
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        if(len == 0)
            return 0;

        int dp[len]; //dp[i]表示到达第i阶的代价
        dp[0] = cost[0];
        dp[1] = cost[1];

        for(int i = 2; i < len; i++) {
            dp[i] = min(dp[i-2], dp[i-1]) + cost[i];
        }

        return min(dp[len-1], dp[len-2]);
    }
};
// TODO 可以不要dp变量，只用first和second两个变量即可
