/*
 * Problem: Dota2 Senate
 * Difficulty: Medium
 * Tags: string, greedy, queue
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> rQueue, dQueue;
        
        for (int i = 0; i < senate.length(); i++) {
            if (senate[i] == 'R') {
                rQueue.push(i);
            } else {
                dQueue.push(i);
            }
        }
        
        while (!rQueue.empty() && !dQueue.empty()) {
            int rIdx = rQueue.front();
            rQueue.pop();
            int dIdx = dQueue.front();
            dQueue.pop();
            
            if (rIdx < dIdx) {
                rQueue.push(rIdx + senate.length());
            } else {
                dQueue.push(dIdx + senate.length());
            }
        }
        
        return rQueue.empty() ? "Dire" : "Radiant";
    }
};