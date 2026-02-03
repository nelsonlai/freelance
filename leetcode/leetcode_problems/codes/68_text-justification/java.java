/**
 * Problem: Text Justification
 * Difficulty: Hard
 * Tags: array, string, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<String> fullJustify(String[] words, int maxWidth) {
        List<String> result = new ArrayList<>();
        int i = 0;
        
        while (i < words.length) {
            List<String> lineWords = new ArrayList<>();
            int lineLength = 0;
            
            // Collect words for current line
            while (i < words.length && lineLength + words[i].length() + lineWords.size() <= maxWidth) {
                lineWords.add(words[i]);
                lineLength += words[i].length();
                i++;
            }
            
            // Build the line
            if (i == words.length || lineWords.size() == 1) {
                // Last line or single word: left-justified
                StringBuilder line = new StringBuilder();
                for (int j = 0; j < lineWords.size(); j++) {
                    if (j > 0) line.append(' ');
                    line.append(lineWords.get(j));
                }
                while (line.length() < maxWidth) {
                    line.append(' ');
                }
                result.add(line.toString());
            } else {
                // Distribute spaces
                int spacesNeeded = maxWidth - lineLength;
                int gaps = lineWords.size() - 1;
                int baseSpaces = spacesNeeded / gaps;
                int extraSpaces = spacesNeeded % gaps;
                
                StringBuilder line = new StringBuilder(lineWords.get(0));
                for (int j = 1; j < lineWords.size(); j++) {
                    int spaces = baseSpaces + (j <= extraSpaces ? 1 : 0);
                    for (int k = 0; k < spaces; k++) {
                        line.append(' ');
                    }
                    line.append(lineWords.get(j));
                }
                result.add(line.toString());
            }
        }
        
        return result;
    }
}