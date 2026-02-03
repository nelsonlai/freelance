/*
 * Problem: Minimum Space Wasted From Packaging
 * Difficulty: Hard
 * Tags: array, sort, search, binary search
 * 
 * Approach: Sort packages, for each supplier try all boxes, use binary search
 * Time Complexity: O(n log n + m * (k log k + n log k)) where n is packages, m is suppliers, k is boxes
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    const int MOD = 1000000007;
    
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        sort(packages.begin(), packages.end());
        long long total = 0;
        for (int p : packages) {
            total += p;
        }
        
        long long result = LLONG_MAX;
        
        for (auto& supplierBoxes : boxes) {
            sort(supplierBoxes.begin(), supplierBoxes.end());
            if (supplierBoxes.back() < packages.back()) {
                continue;
            }
            
            long long wasted = 0;
            int prev = 0;
            
            for (int box : supplierBoxes) {
                auto it = upper_bound(packages.begin() + prev, packages.end(), box);
                int idx = it - packages.begin();
                
                if (idx > prev) {
                    wasted += (long long)box * (idx - prev);
                    prev = idx;
                    if (prev == packages.size()) {
                        break;
                    }
                }
            }
            
            if (prev == packages.size()) {
                result = min(result, wasted - total);
            }
        }
        
        return result == LLONG_MAX ? -1 : result % MOD;
    }
};