/**
 * Problem: Rearrange Spaces Between Words
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String reorderSpaces(String text) {
        String[] words = text.trim().split("\\s+");
        int totalSpaces = 0;
        for (char c : text.toCharArray()) {
            if (c == ' ') {
                totalSpaces++;
            }
        }
        
        if (words.length == 1) {
            return words[0] + " ".repeat(totalSpaces);
        }
        
        int spacesBetween = totalSpaces / (words.length - 1);
        int spacesRemaining = totalSpaces % (words.length - 1);
        
        StringBuilder result = new StringBuilder();
        String spaceStr = " ".repeat(spacesBetween);
        result.append(String.join(spaceStr, words));
        result.append(" ".repeat(spacesRemaining));
        
        return result.toString();
    }
}