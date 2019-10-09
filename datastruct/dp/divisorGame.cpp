// 数字N如果是奇数，它的约数必然都是奇数；若为偶数，则其约数可奇可偶。
// 无论N初始为多大的值，游戏最终只会进行到N=2时结束，那么谁轮到N=2时谁就会赢。
// 因为爱丽丝先手，N初始若为偶数，爱丽丝则只需一直选1，使鲍勃一直面临N为奇数的情况，这样爱丽丝稳赢；

// dp
class Solution {
public:
    vector<int> dp{vector<int>(1001,-1)};
    bool divisorGame(int N) {

        if(N==1) return false;
        if(N==2) return true;
        if(dp[N] != -1)
            return (bool)dp[N];

        dp[N] = 0;
        for(int i = 1; i<N; i++) {
            if(N%i == 0) { // i是N的约数
                if(dp[N-i] == -1) { // 递归计算
                    dp[N-i] = (int)divisorGame(N-i);
                    if(dp[N-i] == 0) { // dp[N] = (!dp[约数1]) || (!dp[约数2]) || ...
                        dp[N] = 1;
                        break;
                    }
                }
            }
        }
        return (bool)dp[N];
    }
};


