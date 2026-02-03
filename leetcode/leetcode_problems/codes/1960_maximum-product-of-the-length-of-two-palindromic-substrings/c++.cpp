/*
 * Problem: Maximum Product of the Length of Two Palindromic Substrings
 * Difficulty: Hard
 * Tags: string, Manacher's algorithm, palindrome
 * 
 * Approach: Use Manacher's algorithm to find all palindromes, maximize product
 * Time Complexity: O(n^2) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> manacher(string s) {
        string sNew = "#";
        for (char c : s) {
            sNew += c;
            sNew += "#";
        }
        int nNew = sNew.length();
        vector<int> p(nNew, 0);
        int center = 0, right = 0;
        
        for (int i = 0; i < nNew; i++) {
            if (i < right) {
                p[i] = min(right - i, p[2 * center - i]);
            }
            
            while (i + p[i] + 1 < nNew && i - p[i] - 1 >= 0 &&
                   sNew[i + p[i] + 1] == sNew[i - p[i] - 1]) {
                p[i]++;
            }
            
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
        
        // Extract palindrome lengths for original string positions
        vector<int> result(s.length());
        for (int i = 1; i < nNew - 1; i += 2) {
            int origPos = (i - 1) / 2;
            result[origPos] = p[i];
        }
        
        return result;
    }
    
public:
    long long maxProduct(string s) {
        int n = s.length();
        vector<int> palLengths = manacher(s);
        
        // Find max product of two non-overlapping palindromes
        long long maxProduct = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len1 = (i < palLengths.size()) ? palLengths[i] : 1;
                int len2 = (j < palLengths.size()) ? palLengths[j] : 1;
                
                // Check if they don't overlap
                int start1 = i - (len1 - 1) / 2;
                int end1 = i + len1 / 2;
                int start2 = j - (len2 - 1) / 2;
                int end2 = j + len2 / 2;
                
                if (end1 < start2) {
                    maxProduct = max(maxProduct, (long long) len1 * len2);
                }
            }
        }
        
        return maxProduct;
    }
};
