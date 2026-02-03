/**
 * Problem: Design Compressed String Iterator
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;
import java.util.regex.*;

class StringIterator {
    private List<Character> chars;
    private List<Integer> counts;
    private int index;

    public StringIterator(String compressedString) {
        chars = new ArrayList<>();
        counts = new ArrayList<>();
        
        Pattern pattern = Pattern.compile("([a-zA-Z])(\\d+)");
        Matcher matcher = pattern.matcher(compressedString);
        
        while (matcher.find()) {
            chars.add(matcher.group(1).charAt(0));
            counts.add(Integer.parseInt(matcher.group(2)));
        }
        
        index = 0;
    }
    
    public char next() {
        if (!hasNext()) {
            return ' ';
        }
        
        char result = chars.get(index);
        counts.set(index, counts.get(index) - 1);
        
        if (counts.get(index) == 0) {
            index++;
        }
        
        return result;
    }
    
    public boolean hasNext() {
        return index < chars.size() && counts.get(index) > 0;
    }
}

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator obj = new StringIterator(compressedString);
 * char param_1 = obj.next();
 * boolean param_2 = obj.hasNext();
 */