/*
 * Problem: Find the Closest Palindrome
 * Difficulty: Hard
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <set>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    string nearestPalindromic(string n) {
        int length = n.length();
        long num = stol(n);
        
        set<long> candidates;
        candidates.insert((long)pow(10, length - 1) - 1);
        candidates.insert((long)pow(10, length) + 1);
        
        long prefix = stol(n.substr(0, (length + 1) / 2));
        for (long i = -1; i <= 1; i++) {
            string candidate = to_string(prefix + i);
            if (length % 2 == 0) {
                string reversed = candidate;
                reverse(reversed.begin(), reversed.end());
                candidate += reversed;
            } else {
                string reversed = candidate.substr(0, candidate.length() - 1);
                reverse(reversed.begin(), reversed.end());
                candidate += reversed;
            }
            candidates.insert(stol(candidate));
        }
        
        candidates.erase(num);
        
        long result = 0;
        long minDiff = LONG_MAX;
        for (long candidate : candidates) {
            long diff = abs(candidate - num);
            if (diff < minDiff || (diff == minDiff && candidate < result)) {
                minDiff = diff;
                result = candidate;
            }
        }
        
        return to_string(result);
    }
};