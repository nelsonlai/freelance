/*
 * Problem: Maximize the Confusion of an Exam
 * Difficulty: Medium
 * Tags: array, string, search, sliding window
 * 
 * Approach: Use sliding window - maximize consecutive T or F with at most k flips
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    int maxConsecutiveChar(string& answerKey, int k, char target) {
        int left = 0;
        int maxLen = 0;
        int count = 0;
        
        for (int right = 0; right < answerKey.length(); right++) {
            if (answerKey[right] != target) {
                count++;
            }
            
            while (count > k) {
                if (answerKey[left] != target) {
                    count--;
                }
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
    
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        return max(maxConsecutiveChar(answerKey, k, 'T'),
                   maxConsecutiveChar(answerKey, k, 'F'));
    }
};