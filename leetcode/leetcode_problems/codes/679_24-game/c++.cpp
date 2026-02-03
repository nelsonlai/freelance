/*
 * Problem: 24 Game
 * Difficulty: Hard
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    bool dfs(vector<double>& nums) {
        if (nums.size() == 1) {
            return abs(nums[0] - 24) < 1e-6;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                double a = nums[i];
                double b = nums[j];
                vector<double> newNums;
                
                for (int k = 0; k < nums.size(); k++) {
                    if (k != i && k != j) {
                        newNums.push_back(nums[k]);
                    }
                }
                
                vector<double> results = {a + b, a - b, b - a, a * b};
                if (b != 0) results.push_back(a / b);
                if (a != 0) results.push_back(b / a);
                
                for (double result : results) {
                    if (isfinite(result)) {
                        newNums.push_back(result);
                        if (dfs(newNums)) {
                            return true;
                        }
                        newNums.pop_back();
                    }
                }
            }
        }
        
        return false;
    }

public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;
        for (int card : cards) {
            nums.push_back((double)card);
        }
        return dfs(nums);
    }
};