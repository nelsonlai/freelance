/*
 * Problem: Minimum Possible Integer After at Most K Adjacent Swaps On Digits
 * Difficulty: Hard
 * Tags: string, tree, greedy
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string minInteger(string num, int k) {
        string num_str = num;
        int n = num_str.length();
        
        for (int i = 0; i < n; i++) {
            if (k <= 0) {
                break;
            }
            
            char min_digit = num_str[i];
            int min_idx = i;
            
            for (int j = i + 1; j < min(i + k + 1, n); j++) {
                if (num_str[j] < min_digit) {
                    min_digit = num_str[j];
                    min_idx = j;
                }
            }
            
            if (min_idx > i) {
                k -= (min_idx - i);
                char temp = num_str[min_idx];
                for (int j = min_idx; j > i; j--) {
                    num_str[j] = num_str[j-1];
                }
                num_str[i] = temp;
            }
        }
        
        return num_str;
    }
};