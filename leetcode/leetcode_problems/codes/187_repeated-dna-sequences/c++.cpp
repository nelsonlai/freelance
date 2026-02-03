/*
 * Problem: Repeated DNA Sequences
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.length() < 10) {
            return {};
        }
        
        unordered_map<string, int> seen;
        vector<string> result;
        
        for (int i = 0; i <= s.length() - 10; i++) {
            string sequence = s.substr(i, 10);
            seen[sequence]++;
            if (seen[sequence] == 2) {
                result.push_back(sequence);
            }
        }
        
        return result;
    }
};