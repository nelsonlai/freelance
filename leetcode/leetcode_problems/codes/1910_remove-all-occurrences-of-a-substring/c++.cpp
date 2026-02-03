/*
 * Problem: Remove All Occurrences of a Substring
 * Difficulty: Medium
 * Tags: string, stack
 * 
 * Approach: Use stack to simulate removal, keep removing until no more occurrences
 * Time Complexity: O(n * m) where n is s length, m is part length
 * Space Complexity: O(n)
 */

#include <string>

using namespace std;

class Solution {
public:
    string removeOccurrences(string s, string part) {
        string result;
        int partLen = part.length();
        
        for (char c : s) {
            result += c;
            if (result.length() >= partLen) {
                string last = result.substr(result.length() - partLen);
                if (last == part) {
                    result = result.substr(0, result.length() - partLen);
                }
            }
        }
        
        return result;
    }
};