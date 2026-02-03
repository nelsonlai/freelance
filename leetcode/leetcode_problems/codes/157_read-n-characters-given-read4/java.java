/**
 * Problem: Read N Characters Given Read4
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char[] buf4);
 */

public class Solution extends Reader4 {
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    public int read(char[] buf, int n) {
        int totalRead = 0;
        char[] buf4 = new char[4];
        
        while (totalRead < n) {
            int count = read4(buf4);
            if (count == 0) {
                break;
            }
            
            for (int i = 0; i < count && totalRead < n; i++) {
                buf[totalRead++] = buf4[i];
            }
        }
        
        return totalRead;
    }
}