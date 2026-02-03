/*
 * Problem: Remove All Adjacent Duplicates in String II
 * Difficulty: Medium
 * Tags: string, tree, stack
 * 
 * Approach: Use stack to track characters and their counts, remove when count reaches k
 * Time Complexity: O(n) where n is the length of s
 * Space Complexity: O(n) for stack
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        vector<pair<char, int>> stack;
        
        for (char c : s) {
            if (!stack.empty() && stack.back().first == c) {
                stack.back().second++;
                if (stack.back().second == k) {
                    stack.pop_back();
                }
            } else {
                stack.push_back({c, 1});
            }
        }
        
        string result;
        for (auto& [ch, count] : stack) {
            result += string(count, ch);
        }
        
        return result;
    }
};