/*
 * Problem: Find Array Given Subset Sums
 * Difficulty: Hard
 * Tags: array, recursion, subset sum
 * 
 * Approach: Recursively recover array from subset sums
 * Time Complexity: O(n * 2^n) where n is array length
 * Space Complexity: O(2^n)
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
private:
    vector<int> recover(vector<int>& current, vector<int>& sums) {
        if (sums.size() == 1) {
            return current;
        }
        
        // Find the smallest non-zero element
        int diff = sums[1] - sums[0];
        
        // Split into two groups: with and without diff
        unordered_map<int, int> counter;
        for (int s : sums) {
            counter[s]++;
        }
        
        vector<int> withoutDiff;
        vector<int> withDiff;
        
        for (int s : sums) {
            if (counter[s] > 0) {
                withoutDiff.push_back(s);
                counter[s]--;
                if (counter[s + diff] > 0) {
                    withDiff.push_back(s + diff);
                    counter[s + diff]--;
                }
            }
        }
        
        // Try positive diff
        if (find(withoutDiff.begin(), withoutDiff.end(), diff) != withoutDiff.end()) {
            vector<int> newCurrent = current;
            newCurrent.push_back(diff);
            vector<int> result = recover(newCurrent, withoutDiff);
            if (!result.empty()) {
                return result;
            }
        }
        
        // Try negative diff
        if (find(withDiff.begin(), withDiff.end(), -diff) != withDiff.end()) {
            vector<int> newCurrent = current;
            newCurrent.push_back(-diff);
            vector<int> result = recover(newCurrent, withoutDiff);
            if (!result.empty()) {
                return result;
            }
        }
        
        return {};
    }
    
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        sort(sums.begin(), sums.end());
        vector<int> current;
        return recover(current, sums);
    }
};
