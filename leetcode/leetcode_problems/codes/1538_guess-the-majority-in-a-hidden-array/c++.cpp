/*
 * Problem: Guess the Majority in a Hidden Array
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares 4 different elements in the array
 *     // return 4 if the values of the 4 elements are the same (0 or 1).
 *     // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 *     // return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 *     int query(int a, int b, int c, int d);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

#include <vector>

using namespace std;

class Solution {
public:
    int guessMajority(ArrayReader &reader) {
        int n = reader.length();
        vector<int> values(n, 0);
        int count0 = 1, count1 = 0;
        
        int q1 = reader.query(0, 1, 2, 3);
        if (q1 == 4) {
            values[1] = values[2] = values[3] = 0;
            count0 += 3;
        } else if (q1 == 0) {
            int q2 = n > 4 ? reader.query(0, 1, 2, 4) : 0;
            if (q2 == 4 || q2 == 2) {
                values[1] = values[2] = 0;
                values[3] = 1;
                count0 += 2;
                count1 += 1;
            } else {
                int q3 = n > 4 ? reader.query(0, 1, 3, 4) : 0;
                if (q3 == 4) {
                    values[1] = values[3] = 0;
                    values[2] = 1;
                    count0 += 2;
                    count1 += 1;
                } else {
                    values[1] = 0;
                    values[2] = values[3] = 1;
                    count0 += 1;
                    count1 += 2;
                }
            }
        } else {
            int q2 = n > 4 ? reader.query(0, 1, 2, 4) : 0;
            if (q2 == 4) {
                values[1] = values[2] = 0;
                values[3] = 1;
                count0 += 2;
                count1 += 1;
            } else {
                values[1] = 0;
                values[2] = values[3] = 1;
                count0 += 1;
                count1 += 2;
            }
        }
        
        for (int i = 4; i < n; i++) {
            int q = reader.query(0, 1, 2, i);
            if (q == 4) {
                values[i] = values[0];
                if (values[i] == 0) count0++;
                else count1++;
            } else if (q == 0) {
                values[i] = 1 - values[0];
                if (values[i] == 0) count0++;
                else count1++;
            } else {
                if (values[1] == values[2]) {
                    values[i] = 1 - values[1];
                } else {
                    int q2 = reader.query(0, 1, 3, i);
                    values[i] = (q2 == 4) ? values[1] : 1 - values[1];
                }
                if (values[i] == 0) count0++;
                else count1++;
            }
        }
        
        if (count0 == count1) return -1;
        if (count0 < count1) {
            for (int i = 0; i < n; i++) {
                if (values[i] == 0) return i;
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (values[i] == 1) return i;
            }
        }
        return -1;
    }
};