/*
 * Problem: Strings Differ by One Character
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool differByOne(vector<string>& dict) {
        int n = dict.size();
        if (n == 0) {
            return false;
        }
        
        int m = dict[0].length();
        
        for (int j = 0; j < m; j++) {
            unordered_set<string> seen;
            for (int i = 0; i < n; i++) {
                string masked = dict[i].substr(0, j) + "*" + dict[i].substr(j + 1);
                if (seen.find(masked) != seen.end()) {
                    return true;
                }
                seen.insert(masked);
            }
        }
        
        return false;
    }
};