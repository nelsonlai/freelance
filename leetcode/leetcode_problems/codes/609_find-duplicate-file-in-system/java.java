/**
 * Problem: Find Duplicate File in System
 * Difficulty: Medium
 * Tags: array, string, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<List<String>> findDuplicate(String[] paths) {
        Map<String, List<String>> contentMap = new HashMap<>();
        
        for (String path : paths) {
            String[] parts = path.split(" ");
            String directory = parts[0];
            
            for (int i = 1; i < parts.length; i++) {
                String fileInfo = parts[i];
                int idx = fileInfo.indexOf('(');
                String name = fileInfo.substring(0, idx);
                String content = fileInfo.substring(idx + 1, fileInfo.length() - 1);
                String fullPath = directory + "/" + name;
                contentMap.computeIfAbsent(content, k -> new ArrayList<>()).add(fullPath);
            }
        }
        
        List<List<String>> result = new ArrayList<>();
        for (List<String> paths : contentMap.values()) {
            if (paths.size() > 1) {
                result.add(paths);
            }
        }
        
        return result;
    }
}