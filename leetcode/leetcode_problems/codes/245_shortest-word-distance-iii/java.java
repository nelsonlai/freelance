/**
 * Problem: Shortest Word Distance III
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int shortestWordDistance(String[] wordsDict, String word1, String word2) {
        int index1 = -1;
        int index2 = -1;
        int minDistance = Integer.MAX_VALUE;
        
        for (int i = 0; i < wordsDict.length; i++) {
            if (wordsDict[i].equals(word1)) {
                if (word1.equals(word2) && index1 != -1) {
                    minDistance = Math.min(minDistance, i - index1);
                }
                index1 = i;
                if (index2 != -1) {
                    minDistance = Math.min(minDistance, Math.abs(index1 - index2));
                }
            } else if (wordsDict[i].equals(word2)) {
                index2 = i;
                if (index1 != -1) {
                    minDistance = Math.min(minDistance, Math.abs(index1 - index2));
                }
            }
        }
        
        return minDistance;
    }
}