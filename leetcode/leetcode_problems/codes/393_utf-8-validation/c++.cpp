/*
 * Problem: UTF-8 Validation
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int i = 0;
        while (i < data.size()) {
            int byte = data[i];
            
            if ((byte >> 7) == 0) {
                i++;
            } else if ((byte >> 5) == 0b110) {
                if (i + 1 >= data.size() || (data[i + 1] >> 6) != 0b10) {
                    return false;
                }
                i += 2;
            } else if ((byte >> 4) == 0b1110) {
                if (i + 2 >= data.size() || (data[i + 1] >> 6) != 0b10 || (data[i + 2] >> 6) != 0b10) {
                    return false;
                }
                i += 3;
            } else if ((byte >> 3) == 0b11110) {
                if (i + 3 >= data.size() || (data[i + 1] >> 6) != 0b10 || 
                    (data[i + 2] >> 6) != 0b10 || (data[i + 3] >> 6) != 0b10) {
                    return false;
                }
                i += 4;
            } else {
                return false;
            }
        }
        
        return true;
    }
};