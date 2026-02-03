/*
 * Problem: The kth Factor of n
 * Difficulty: Medium
 * Tags: math, sort
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> factors;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                factors.push_back(i);
                if (i != n / i) {
                    factors.push_back(n / i);
                }
            }
        }
        
        sort(factors.begin(), factors.end());
        return k <= factors.size() ? factors[k - 1] : -1;
    }
};