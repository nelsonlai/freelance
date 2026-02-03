/*
 * Problem: Repeated String Match
 * Difficulty: Medium
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>

using namespace std;

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        if (b.empty()) {
            return 0;
        }
        
        int count = (b.length() + a.length() - 1) / a.length();
        string repeated = "";
        for (int i = 0; i < count; i++) {
            repeated += a;
        }
        
        if (repeated.find(b) != string::npos) {
            return count;
        }
        
        repeated += a;
        if (repeated.find(b) != string::npos) {
            return count + 1;
        }
        
        return -1;
    }
};