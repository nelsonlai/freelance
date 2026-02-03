/*
 * Problem: Maximum Product of Word Lengths
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        vector<int> masks(n, 0);
        
        for (int i = 0; i < n; i++) {
            for (char c : words[i]) {
                masks[i] |= 1 << (c - 'a');
            }
        }
        
        int maxProduct = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((masks[i] & masks[j]) == 0) {
                    maxProduct = max(maxProduct, (int)(words[i].length() * words[j].length()));
                }
            }
        }
        
        return maxProduct;
    }
};