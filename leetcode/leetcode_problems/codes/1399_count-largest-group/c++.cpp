/*
 * Problem: Count Largest Group
 * Difficulty: Easy
 * Tags: math, hash
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    int digitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

public:
    int countLargestGroup(int n) {
        unordered_map<int, int> groups;
        for (int i = 1; i <= n; i++) {
            groups[digitSum(i)]++;
        }
        
        int maxSize = 0;
        for (auto& entry : groups) {
            maxSize = max(maxSize, entry.second);
        }
        
        int count = 0;
        for (auto& entry : groups) {
            if (entry.second == maxSize) {
                count++;
            }
        }
        
        return count;
    }
};