/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        if (reader.get(0) == target) {
            return 0;
        }
        
        int left = 0, right = 1;
        while (reader.get(right) < target) {
            left = right;
            right <<= 1;
        }
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = reader.get(mid);
            if (val == target) {
                return mid;
            } else if (val > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return -1;
    }
};
