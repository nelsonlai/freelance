/**
 * Problem: Making File Names Unique
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String[] getFolderNames(String[] names) {
        Set<String> used = new HashSet<>();
        String[] result = new String[names.length];
        
        for (int i = 0; i < names.length; i++) {
            String name = names[i];
            if (!used.contains(name)) {
                result[i] = name;
                used.add(name);
            } else {
                int k = 1;
                String newName;
                do {
                    newName = name + "(" + k + ")";
                    k++;
                } while (used.contains(newName));
                result[i] = newName;
                used.add(newName);
            }
        }
        
        return result;
    }
}