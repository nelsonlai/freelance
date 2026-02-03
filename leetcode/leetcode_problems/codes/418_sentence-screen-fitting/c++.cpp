/*
 * Problem: Sentence Screen Fitting
 * Difficulty: Medium
 * Tags: array, string, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        string s = "";
        for (string word : sentence) {
            s += word + " ";
        }
        
        int start = 0;
        int n = s.length();
        
        for (int i = 0; i < rows; i++) {
            start += cols;
            if (s[start % n] == ' ') {
                start++;
            } else {
                while (start > 0 && s[(start - 1) % n] != ' ') {
                    start--;
                }
            }
        }
        
        return start / n;
    }
};