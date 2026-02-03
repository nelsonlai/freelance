/*
 * Problem: Longest Happy String
 * Difficulty: Medium
 * Tags: string, tree, greedy, queue, heap
 * 
 * Approach: Greedy - use heap to always pick most frequent char (if can't use same twice)
 * Time Complexity: O(n log 3) where n is total characters
 * Space Complexity: O(n) for result
 */

#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> heap;
        if (a > 0) heap.push({a, 'a'});
        if (b > 0) heap.push({b, 'b'});
        if (c > 0) heap.push({c, 'c'});
        
        string result;
        
        while (!heap.empty()) {
            auto [count1, char1] = heap.top();
            heap.pop();
            
            if (result.length() >= 2 && result.back() == char1 && result[result.length() - 2] == char1) {
                if (heap.empty()) {
                    break;
                }
                auto [count2, char2] = heap.top();
                heap.pop();
                result += char2;
                count2--;
                if (count2 > 0) {
                    heap.push({count2, char2});
                }
                heap.push({count1, char1});
            } else {
                result += char1;
                count1--;
                if (count1 > 0) {
                    heap.push({count1, char1});
                }
            }
        }
        
        return result;
    }
};