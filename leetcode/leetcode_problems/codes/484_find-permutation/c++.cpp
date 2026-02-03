/*
 * Problem: Find Permutation
 * Difficulty: Medium
 * Tags: array, string, graph, greedy, stack
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
    vector<int> findPermutation(string s) {
        int n = s.length() + 1;
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = i + 1;
        }
        
        int i = 0;
        while (i < s.length()) {
            if (s[i] == 'D') {
                int j = i;
                while (j < s.length() && s[j] == 'D') {
                    j++;
                }
                reverse(result.begin() + i, result.begin() + j + 1);
                i = j;
            } else {
                i++;
            }
        }
        
        return result;
    }
};