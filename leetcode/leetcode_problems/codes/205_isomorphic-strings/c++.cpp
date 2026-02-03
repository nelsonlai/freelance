/*
 * Problem: Isomorphic Strings
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        
        unordered_map<char, char> sToT;
        unordered_map<char, char> tToS;
        
        for (int i = 0; i < s.length(); i++) {
            char sChar = s[i];
            char tChar = t[i];
            
            if (sToT.find(sChar) != sToT.end()) {
                if (sToT[sChar] != tChar) {
                    return false;
                }
            } else {
                sToT[sChar] = tChar;
            }
            
            if (tToS.find(tChar) != tToS.end()) {
                if (tToS[tChar] != sChar) {
                    return false;
                }
            } else {
                tToS[tChar] = sChar;
            }
        }
        
        return true;
    }
};