/**
 * Problem: Reorder Data in Log Files
 * Difficulty: Medium
 * Tags: array, string, graph, sort
 * 
 * Approach: Separate letter logs and digit logs, sort letter logs by content then identifier
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for separating logs
 */

import java.util.*;

class Solution {
    public String[] reorderLogFiles(String[] logs) {
        List<String> letterLogs = new ArrayList<>();
        List<String> digitLogs = new ArrayList<>();
        
        for (String log : logs) {
            int spaceIdx = log.indexOf(' ');
            String content = log.substring(spaceIdx + 1);
            if (Character.isDigit(content.charAt(0))) {
                digitLogs.add(log);
            } else {
                letterLogs.add(log);
            }
        }
        
        letterLogs.sort((a, b) -> {
            int spaceIdxA = a.indexOf(' ');
            int spaceIdxB = b.indexOf(' ');
            String contentA = a.substring(spaceIdxA + 1);
            String contentB = b.substring(spaceIdxB + 1);
            int cmp = contentA.compareTo(contentB);
            if (cmp != 0) return cmp;
            return a.substring(0, spaceIdxA).compareTo(b.substring(0, spaceIdxB));
        });
        
        letterLogs.addAll(digitLogs);
        return letterLogs.toArray(new String[0]);
    }
}