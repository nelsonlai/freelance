/*
 * Problem: Incremental Memory Leak
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Simulate memory leak, allocate to larger memory block
 * Time Complexity: O(sqrt(memory1 + memory2))
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> memLeak(int memory1, int memory2) {
        int time = 1;
        
        while (true) {
            if (memory1 >= memory2) {
                if (memory1 < time) {
                    return {time, memory1, memory2};
                }
                memory1 -= time;
            } else {
                if (memory2 < time) {
                    return {time, memory1, memory2};
                }
                memory2 -= time;
            }
            time++;
        }
    }
};