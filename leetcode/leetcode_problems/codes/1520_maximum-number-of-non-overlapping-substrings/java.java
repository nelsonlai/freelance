/**
 * Problem: Maximum Number of Non-Overlapping Substrings
 * Difficulty: Hard
 * Tags: string, tree, greedy
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<String> maxNumOfSubstrings(String s) {
        Map<Character, Integer> first = new HashMap<>();
        Map<Character, Integer> last = new HashMap<>();
        
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (!first.containsKey(c)) {
                first.put(c, i);
            }
            last.put(c, i);
        }
        
        List<int[]> intervals = new ArrayList<>();
        Set<Character> chars = new HashSet<>();
        for (char c : s.toCharArray()) {
            chars.add(c);
        }
        
        for (char c : chars) {
            int[] interval = extend(s, first.get(c), last.get(c), first, last);
            if (interval != null) {
                intervals.add(interval);
            }
        }
        
        intervals.sort((a, b) -> {
            if (a[1] != b[1]) {
                return Integer.compare(a[1], b[1]);
            }
            return Integer.compare(a[0], b[0]);
        });
        
        List<String> result = new ArrayList<>();
        int prevEnd = -1;
        for (int[] interval : intervals) {
            if (interval[0] > prevEnd) {
                result.add(s.substring(interval[0], interval[1] + 1));
                prevEnd = interval[1];
            }
        }
        
        return result;
    }
    
    private int[] extend(String s, int start, int end, Map<Character, Integer> first, Map<Character, Integer> last) {
        int right = end;
        int i = start;
        while (i <= right) {
            char c = s.charAt(i);
            if (first.get(c) < start) {
                return null;
            }
            right = Math.max(right, last.get(c));
            i++;
        }
        return new int[]{start, right};
    }
}