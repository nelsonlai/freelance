/*
 * Problem: Number of Ways to Reorder Array to Get Same BST
 * Difficulty: Hard
 * Tags: array, tree, graph, dp, math, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>

using namespace std;

class Solution {
private:
    static const int MOD = 1000000007;
    
    long long nCr(int n, int r) {
        if (r > n || r < 0) {
            return 0;
        }
        if (r == 0 || r == n) {
            return 1;
        }
        r = min(r, n - r);
        long long result = 1;
        for (int i = 0; i < r; i++) {
            result = result * (n - i) / (i + 1);
        }
        return result % MOD;
    }
    
    long long ways(vector<int>& arr) {
        if (arr.size() <= 2) {
            return 1;
        }
        
        int root = arr[0];
        vector<int> left, right;
        
        for (int x : arr) {
            if (x < root) {
                left.push_back(x);
            } else if (x > root) {
                right.push_back(x);
            }
        }
        
        long long leftWays = ways(left);
        long long rightWays = ways(right);
        
        return nCr(left.size() + right.size(), left.size()) * leftWays % MOD * rightWays % MOD;
    }
    
public:
    int numOfWays(vector<int>& nums) {
        return (ways(nums) - 1) % MOD;
    }
};