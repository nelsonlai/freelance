/*
 * Problem: Logger Rate Limiter
 * Difficulty: Easy
 * Tags: string, dp, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <unordered_map>

using namespace std;

class Logger {
private:
    unordered_map<string, int> messageTimestamp;

public:
    Logger() {
        
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        if (messageTimestamp.find(message) == messageTimestamp.end() || 
            timestamp - messageTimestamp[message] >= 10) {
            messageTimestamp[message] = timestamp;
            return true;
        }
        return false;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */