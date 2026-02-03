/**
 * Problem: Check if Numbers Are Ascending in a Sentence
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Extract all numbers, check if they form strictly increasing sequence
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(k) where k is number of numbers
 */

class Solution {
    public boolean areNumbersAscending(String s) {
        String[] words = s.split(" ");
        List<Integer> numbers = new ArrayList<>();
        
        for (String word : words) {
            try {
                int num = Integer.parseInt(word);
                numbers.add(num);
            } catch (NumberFormatException e) {
                // Not a number, skip
            }
        }
        
        for (int i = 1; i < numbers.size(); i++) {
            if (numbers.get(i) <= numbers.get(i - 1)) {
                return false;
            }
        }
        
        return true;
    }
}