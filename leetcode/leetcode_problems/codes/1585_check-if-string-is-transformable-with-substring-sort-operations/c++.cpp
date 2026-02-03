/*
 * Problem: Check If String Is Transformable With Substring Sort Operations
 * Difficulty: Hard
 * Tags: string, tree, greedy, sort
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool isTransformable(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        
        vector<queue<int>> positions(10);
        for (int i = 0; i < s.length(); i++) {
            positions[s[i] - '0'].push(i);
        }
        
        for (char c : t) {
            int digit = c - '0';
            if (positions[digit].empty()) {
                return false;
            }
            
            int pos = positions[digit].front();
            for (int smaller = 0; smaller < digit; smaller++) {
                if (!positions[smaller].empty() && positions[smaller].front() < pos) {
                    return false;
                }
            }
            
            positions[digit].pop();
        }
        
        return true;
    }
};