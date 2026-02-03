/*
 * Problem: H-Index
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), greater<int>());
        
        for (int i = 0; i < citations.size(); i++) {
            if (i + 1 > citations[i]) {
                return i;
            }
        }
        
        return citations.size();
    }
};