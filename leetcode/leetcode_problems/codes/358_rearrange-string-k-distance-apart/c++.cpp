/*
 * Problem: Rearrange String k Distance Apart
 * Difficulty: Hard
 * Tags: string, greedy, hash, sort, queue, heap
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    string rearrangeString(string s, int k) {
        if (k == 0) {
            return s;
        }
        
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        priority_queue<pair<int, char>> heap;
        for (auto& entry : count) {
            heap.push({entry.second, entry.first});
        }
        
        string result;
        queue<pair<int, char>> waitQueue;
        
        while (!heap.empty()) {
            auto [freq, char] = heap.top();
            heap.pop();
            result += char;
            
            if (freq - 1 > 0) {
                waitQueue.push({freq - 1, char});
            }
            
            if (waitQueue.size() >= k) {
                auto [freq, char] = waitQueue.front();
                waitQueue.pop();
                heap.push({freq, char});
            }
        }
        
        return waitQueue.empty() && result.length() == s.length() ? result : "";
    }
};