#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        int k = s.length();
        vector<int> dp(k + 1, 0);
        dp[k] = 1;
        
        for (int i = k - 1; i >= 0; i--) {
            int si = s[i] - '0';
            for (string d : digits) {
                int digit = stoi(d);
                if (digit < si) {
                    dp[i] += pow(digits.size(), k - i - 1);
                } else if (digit == si) {
                    dp[i] += dp[i + 1];
                }
            }
        }
        
        int result = dp[0];
        for (int i = 1; i < k; i++) {
            result += pow(digits.size(), i);
        }
        return result;
    }
};
