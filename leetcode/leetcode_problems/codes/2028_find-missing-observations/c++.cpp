/*
 * Problem: Find Missing Observations
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Calculate total needed, distribute evenly with constraints (1-6 per die)
 * Time Complexity: O(n) where n is missing observations
 * Space Complexity: O(n)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int total = mean * (m + n);
        int observedSum = 0;
        for (int roll : rolls) {
            observedSum += roll;
        }
        int missingSum = total - observedSum;
        
        if (missingSum < n || missingSum > 6 * n) {
            return {};
        }
        
        // Distribute evenly
        int base = missingSum / n;
        int remainder = missingSum % n;
        
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = base;
            if (i < remainder) {
                result[i]++;
            }
        }
        
        // Validate all are in range [1, 6]
        for (int val : result) {
            if (val < 1 || val > 6) {
                return {};
            }
        }
        
        return result;
    }
};