#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map<string, double> memo;
    
    double dp(int a, int b) {
        if (a <= 0 && b <= 0) {
            return 0.5;
        }
        if (a <= 0) {
            return 1.0;
        }
        if (b <= 0) {
            return 0.0;
        }
        string key = to_string(a) + "," + to_string(b);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        double result = 0.25 * (dp(a-100, b) + dp(a-75, b-25) + dp(a-50, b-50) + dp(a-25, b-75));
        memo[key] = result;
        return result;
    }

public:
    double soupServings(int n) {
        if (n > 4800) {
            return 1.0;
        }
        return dp(n, n);
    }
};
