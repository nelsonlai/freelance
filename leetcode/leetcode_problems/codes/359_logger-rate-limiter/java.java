/**
 * Problem: Logger Rate Limiter
 * Difficulty: Easy
 * Tags: string, dp, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Logger {
    private Map<String, Integer> messageTimestamp;

    public Logger() {
        messageTimestamp = new HashMap<>();
    }
    
    public boolean shouldPrintMessage(int timestamp, String message) {
        if (!messageTimestamp.containsKey(message) || 
            timestamp - messageTimestamp.get(message) >= 10) {
            messageTimestamp.put(message, timestamp);
            return true;
        }
        return false;
    }
}

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * boolean param_1 = obj.shouldPrintMessage(timestamp,message);
 */