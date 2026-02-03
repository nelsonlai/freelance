/*
 * Problem: Maximum Product of the Length of Two Palindromic Subsequences
 * Difficulty: Medium
 * Tags: string, dp, bitmask
 * 
 * Approach: Use bitmask to enumerate all subsequences, find palindromic ones, maximize product
 * Time Complexity: O(3^n) where n is length
 * Space Complexity: O(2^n)
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isPalindrome(string& s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    
public:
    int maxProduct(string s) {
        int n = s.length();
        vector<int> palindromes;
        
        // Find all palindromic subsequences
        for (int mask = 1; mask < (1 << n); mask++) {
            string subseq;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subseq += s[i];
                }
            }
            
            if (isPalindrome(subseq)) {
                palindromes.push_back(mask);
            }
        }
        
        int maxProduct = 0;
        
        // Find two non-overlapping palindromic subsequences
        for (int i = 0; i < palindromes.size(); i++) {
            for (int j = i + 1; j < palindromes.size(); j++) {
                if ((palindromes[i] & palindromes[j]) == 0) {  // No overlap
                    int len1 = __builtin_popcount(palindromes[i]);
                    int len2 = __builtin_popcount(palindromes[j]);
                    maxProduct = max(maxProduct, len1 * len2);
                }
            }
        }
        
        return maxProduct;
    }
};