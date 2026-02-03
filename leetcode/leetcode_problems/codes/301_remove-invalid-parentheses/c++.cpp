/*
 * Problem: Remove Invalid Parentheses
 * Difficulty: Hard
 * Tags: string, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void remove(string s, int lastI, int lastJ, vector<char> pair, vector<string>& result) {
        int count = 0;
        for (int i = lastI; i < s.length(); i++) {
            if (s[i] == pair[0]) count++;
            if (s[i] == pair[1]) count--;
            if (count >= 0) continue;
            
            for (int j = lastJ; j <= i; j++) {
                if (s[j] == pair[1] && (j == lastJ || s[j - 1] != pair[1])) {
                    remove(s.substr(0, j) + s.substr(j + 1), i, j, pair, result);
                }
            }
            return;
        }
        
        string reversed(s.rbegin(), s.rend());
        if (pair[0] == '(') {
            remove(reversed, 0, 0, {')', '('}, result);
        } else {
            result.push_back(reversed);
        }
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        remove(s, 0, 0, {'(', ')'}, result);
        return result;
    }
};