/**
 * Problem: Student Attendance Record I
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean checkRecord(String s) {
        int countA = 0;
        int countL = 0;
        
        for (char c : s.toCharArray()) {
            if (c == 'A') {
                countA++;
                if (countA >= 2) {
                    return false;
                }
                countL = 0;
            } else if (c == 'L') {
                countL++;
                if (countL >= 3) {
                    return false;
                }
            } else {
                countL = 0;
            }
        }
        
        return true;
    }
}