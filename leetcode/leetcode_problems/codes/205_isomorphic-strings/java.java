/**
 * Problem: Isomorphic Strings
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean isIsomorphic(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        
        Map<Character, Character> sToT = new HashMap<>();
        Map<Character, Character> tToS = new HashMap<>();
        
        for (int i = 0; i < s.length(); i++) {
            char sChar = s.charAt(i);
            char tChar = t.charAt(i);
            
            if (sToT.containsKey(sChar)) {
                if (sToT.get(sChar) != tChar) {
                    return false;
                }
            } else {
                sToT.put(sChar, tChar);
            }
            
            if (tToS.containsKey(tChar)) {
                if (tToS.get(tChar) != sChar) {
                    return false;
                }
            } else {
                tToS.put(tChar, sChar);
            }
        }
        
        return true;
    }
}