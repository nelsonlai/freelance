/*
 * Problem: Add Bold Tag in String
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string addBoldTag(string s, vector<string>& words) {
        int n = s.length();
        vector<bool> bold(n, false);
        
        for (string word : words) {
            size_t pos = s.find(word);
            while (pos != string::npos) {
                for (int i = pos; i < pos + word.length(); i++) {
                    bold[i] = true;
                }
                pos = s.find(word, pos + 1);
            }
        }
        
        string result = "";
        int i = 0;
        while (i < n) {
            if (bold[i]) {
                result += "<b>";
                while (i < n && bold[i]) {
                    result += s[i];
                    i++;
                }
                result += "</b>";
            } else {
                result += s[i];
                i++;
            }
        }
        
        return result;
    }
};