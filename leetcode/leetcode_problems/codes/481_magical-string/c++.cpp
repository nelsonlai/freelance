/*
 * Problem: Magical String
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    int magicalString(int n) {
        if (n == 0) {
            return 0;
        }
        
        vector<int> s = {1, 2, 2};
        int i = 2;
        
        while (s.size() < n) {
            int nextNum = 3 - s.back();
            int count = s[i];
            for (int j = 0; j < count; j++) {
                s.push_back(nextNum);
            }
            i++;
        }
        
        int result = 0;
        for (int j = 0; j < n; j++) {
            if (s[j] == 1) {
                result++;
            }
        }
        
        return result;
    }
};