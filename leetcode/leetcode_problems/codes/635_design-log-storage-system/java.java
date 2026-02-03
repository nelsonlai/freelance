/**
 * Problem: Design Log Storage System
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class LogSystem {
    private List<int[]> logs;
    private Map<String, Integer> granularityMap;

    public LogSystem() {
        logs = new ArrayList<>();
        granularityMap = new HashMap<>();
        granularityMap.put("Year", 4);
        granularityMap.put("Month", 7);
        granularityMap.put("Day", 10);
        granularityMap.put("Hour", 13);
        granularityMap.put("Minute", 16);
        granularityMap.put("Second", 19);
    }
    
    public void put(int id, String timestamp) {
        logs.add(new int[]{id, Integer.parseInt(timestamp.replace(":", ""))});
    }
    
    public List<Integer> retrieve(String start, String end, String granularity) {
        int idx = granularityMap.get(granularity);
        int startPrefix = Integer.parseInt(start.substring(0, idx).replace(":", ""));
        int endPrefix = Integer.parseInt(end.substring(0, idx).replace(":", ""));
        
        List<Integer> result = new ArrayList<>();
        for (int[] log : logs) {
            String timestamp = String.valueOf(log[1]);
            while (timestamp.length() < 19) {
                timestamp = "0" + timestamp;
            }
            int prefix = Integer.parseInt(timestamp.substring(0, idx));
            if (prefix >= startPrefix && prefix <= endPrefix) {
                result.add(log[0]);
            }
        }
        
        return result;
    }
}

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * List<Integer> param_2 = obj.retrieve(start,end,granularity);
 */