/**
 * Problem: Number of Valid Words in a Sentence
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Check each word against validation rules
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int countValidWords(String sentence) {
        String[] words = sentence.split("\\s+");
        int count = 0;
        
        for (String word : words) {
            if (word.isEmpty()) continue;
            if (isValid(word)) {
                count++;
            }
        }
        
        return count;
    }
    
    private boolean isValid(String word) {
        // Check for digits
        for (char c : word.toCharArray()) {
            if (Character.isDigit(c)) {
                return false;
            }
        }
        
        // Count hyphens and punctuation
        int hyphenCount = 0;
        int punctCount = 0;
        for (char c : word.toCharArray()) {
            if (c == '-') hyphenCount++;
            if (c == '!' || c == '.' || c == ',') punctCount++;
        }
        
        if (hyphenCount > 1 || punctCount > 1) {
            return false;
        }
        
        // Hyphen must be between letters
        int hyphenIdx = word.indexOf('-');
        if (hyphenIdx != -1) {
            if (hyphenIdx == 0 || hyphenIdx == word.length() - 1) {
                return false;
            }
            if (!Character.isLetter(word.charAt(hyphenIdx - 1)) || 
                !Character.isLetter(word.charAt(hyphenIdx + 1))) {
                return false;
            }
        }
        
        // Punctuation must be at the end
        for (char c : new char[]{'!', '.', ','}) {
            int idx = word.indexOf(c);
            if (idx != -1 && idx != word.length() - 1) {
                return false;
            }
        }
        
        return true;
    }
}