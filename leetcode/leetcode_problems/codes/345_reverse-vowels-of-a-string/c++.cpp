/*
 * Problem: Reverse Vowels of a String
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int left = 0, right = s.length() - 1;
        
        while (left < right) {
            while (left < right && vowels.find(s[left]) == vowels.end()) {
                left++;
            }
            while (left < right && vowels.find(s[right]) == vowels.end()) {
                right--;
            }
            
            if (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        
        return s;
    }
};