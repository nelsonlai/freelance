/*
 * Problem: Split a String Into the Max Number of Unique Substrings
 * Difficulty: Medium
 * Tags: string, tree, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    int backtrack(string& s, int start, unordered_set<string>& seen) {
        if (start == s.length()) {
            return 0;
        }
        
        int result = 0;
        for (int end = start + 1; end <= s.length(); end++) {
            string substring = s.substr(start, end - start);
            if (seen.find(substring) == seen.end()) {
                seen.insert(substring);
                result = max(result, 1 + backtrack(s, end, seen));
                seen.erase(substring);
            }
        }
        
        return result;
    }
    
public:
    int maxUniqueSplit(string s) {
        unordered_set<string> seen;
        return backtrack(s, 0, seen);
    }
};