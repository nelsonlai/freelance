/*
 * Problem: Number of Good Ways to Split a String
 * Difficulty: Medium
 * Tags: string, dp, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int numSplits(string s) {
        int n = s.length();
        vector<int> leftDistinct(n);
        vector<int> rightDistinct(n);
        
        unordered_set<char> seen;
        for (int i = 0; i < n; i++) {
            seen.insert(s[i]);
            leftDistinct[i] = seen.size();
        }
        
        seen.clear();
        for (int i = n - 1; i >= 0; i--) {
            seen.insert(s[i]);
            rightDistinct[i] = seen.size();
        }
        
        int count = 0;
        for (int i = 0; i < n - 1; i++) {
            if (leftDistinct[i] == rightDistinct[i + 1]) {
                count++;
            }
        }
        
        return count;
    }
};