/**
 * Problem: Confusing Number
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Rotate digits 180 degrees, check if result is different and valid
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

class Solution {
    public boolean confusingNumber(int n) {
        Map<Integer, Integer> rotateMap = new HashMap<>();
        rotateMap.put(0, 0);
        rotateMap.put(1, 1);
        rotateMap.put(6, 9);
        rotateMap.put(8, 8);
        rotateMap.put(9, 6);
        
        int rotated = 0;
        int original = n;
        
        while (n > 0) {
            int digit = n % 10;
            if (!rotateMap.containsKey(digit)) {
                return false;
            }
            rotated = rotated * 10 + rotateMap.get(digit);
            n /= 10;
        }
        
        return rotated != original;
    }
}