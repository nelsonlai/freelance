/*
 * Problem: String Compression
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0;
        int read = 0;
        
        while (read < chars.size()) {
            char currentChar = chars[read];
            int count = 0;
            
            while (read < chars.size() && chars[read] == currentChar) {
                read++;
                count++;
            }
            
            chars[write++] = currentChar;
            
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }
        
        return write;
    }
};