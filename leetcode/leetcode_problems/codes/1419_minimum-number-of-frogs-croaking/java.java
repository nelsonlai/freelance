/**
 * Problem: Minimum Number of Frogs Croaking
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: Track count of each letter in 'croak', need max concurrent frogs
 * Time Complexity: O(n) where n is length of string
 * Space Complexity: O(1)
 */

class Solution {
    public int minNumberOfFrogs(String croakOfFrogs) {
        int[] count = new int[5];
        int maxFrogs = 0;
        int activeFrogs = 0;
        
        Map<Character, Integer> charToIndex = new HashMap<>();
        charToIndex.put('c', 0);
        charToIndex.put('r', 1);
        charToIndex.put('o', 2);
        charToIndex.put('a', 3);
        charToIndex.put('k', 4);
        
        for (char c : croakOfFrogs.toCharArray()) {
            if (!charToIndex.containsKey(c)) {
                return -1;
            }
            
            int idx = charToIndex.get(c);
            count[idx]++;
            
            if (c == 'c') {
                activeFrogs++;
                maxFrogs = Math.max(maxFrogs, activeFrogs);
            } else if (c == 'k') {
                activeFrogs--;
            }
            
            if (!(count[0] >= count[1] && count[1] >= count[2] && 
                  count[2] >= count[3] && count[3] >= count[4])) {
                return -1;
            }
        }
        
        return activeFrogs == 0 ? maxFrogs : -1;
    }
}