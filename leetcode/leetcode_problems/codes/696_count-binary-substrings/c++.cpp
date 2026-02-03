/*
 * Problem: Count Binary Substrings
 * Difficulty: Easy
 * Tags: array, string, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countBinarySubstrings(string s) {
        vector<int> groups;
        int count = 1;
        
        for (int i = 1; i < s.length(); i++) {
            if (s[i] != s[i-1]) {
                groups.push_back(count);
                count = 1;
            } else {
                count++;
            }
        }
        groups.push_back(count);
        
        int result = 0;
        for (int i = 1; i < groups.size(); i++) {
            result += min(groups[i-1], groups[i]);
        }
        
        return result;
    }
};