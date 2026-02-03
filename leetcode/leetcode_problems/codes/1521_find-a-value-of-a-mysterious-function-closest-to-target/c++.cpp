/*
 * Problem: Find a Value of a Mysterious Function Closest to Target
 * Difficulty: Hard
 * Tags: array, tree, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        int result = INT_MAX;
        
        for (int i = 0; i < arr.size(); i++) {
            int currentAnd = arr[i];
            result = min(result, abs(currentAnd - target));
            
            for (int j = i + 1; j < arr.size(); j++) {
                currentAnd &= arr[j];
                result = min(result, abs(currentAnd - target));
                
                if (currentAnd < target) {
                    break;
                }
            }
        }
        
        return result;
    }
};