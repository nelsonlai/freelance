#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
private:
    unordered_map<int, int> memo;
    
    int dp(int t) {
        if (memo.find(t) != memo.end()) {
            return memo[t];
        }
        
        int n = 32 - __builtin_clz(t);
        if (t == (1 << n) - 1) {
            memo[t] = n;
            return n;
        }
        
        int result = n + 1 + dp((1 << n) - 1 - t);
        for (int m = 0; m < n - 1; m++) {
            result = min(result, n + m + 1 + dp(t - (1 << (n - 1)) + (1 << m)));
        }
        memo[t] = result;
        return result;
    }

public:
    int racecar(int target) {
        return dp(target);
    }
};
