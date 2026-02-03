/**
 * Problem: Next Closest Time
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String nextClosestTime(String time) {
        Set<Character> digits = new HashSet<>();
        for (char c : time.toCharArray()) {
            if (c != ':') {
                digits.add(c);
            }
        }
        
        char[] timeArray = time.replace(":", "").toCharArray();
        
        for (int i = 3; i >= 0; i--) {
            for (char digit : digits) {
                if (digit > timeArray[i]) {
                    timeArray[i] = digit;
                    for (int j = i + 1; j < 4; j++) {
                        timeArray[j] = Collections.min(digits);
                    }
                    String candidate = new String(timeArray);
                    if (candidate.substring(0, 2).compareTo("24") < 0 && 
                        candidate.substring(2).compareTo("60") < 0) {
                        return candidate.substring(0, 2) + ":" + candidate.substring(2);
                    }
                }
            }
            timeArray[i] = Collections.min(digits);
        }
        
        char minDigit = Collections.min(digits);
        return "" + minDigit + minDigit + ":" + minDigit + minDigit;
    }
}