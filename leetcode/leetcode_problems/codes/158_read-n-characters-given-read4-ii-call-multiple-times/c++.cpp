/*
 * Problem: Read N Characters Given read4 II - Call Multiple Times
 * Difficulty: Hard
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
private:
    char buffer[4];
    int bufferSize = 0;
    int bufferIndex = 0;

public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int totalRead = 0;
        
        while (totalRead < n) {
            if (bufferIndex >= bufferSize) {
                bufferSize = read4(buffer);
                bufferIndex = 0;
                if (bufferSize == 0) {
                    break;
                }
            }
            
            buf[totalRead++] = buffer[bufferIndex++];
        }
        
        return totalRead;
    }
};