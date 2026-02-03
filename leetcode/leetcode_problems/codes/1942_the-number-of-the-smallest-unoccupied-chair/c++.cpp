/*
 * Problem: The Number of the Smallest Unoccupied Chair
 * Difficulty: Medium
 * Tags: array, hash, queue, heap
 * 
 * Approach: Use heap to track available chairs and occupied chairs
 * Time Complexity: O(n log n) where n is friends
 * Space Complexity: O(n)
 */

#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size();
        vector<vector<int>> events;
        for (int i = 0; i < n; i++) {
            events.push_back({times[i][0], 1, i});
            events.push_back({times[i][1], 0, i});
        }
        
        sort(events.begin(), events.end());
        
        priority_queue<int, vector<int>, greater<int>> available;
        for (int i = 0; i < n; i++) {
            available.push(i);
        }
        
        map<int, int> chairMap;
        
        for (auto& event : events) {
            int time = event[0];
            int type = event[1];
            int friend_ = event[2];
            
            if (type == 0) {  // leave
                int chair = chairMap[friend_];
                chairMap.erase(friend_);
                available.push(chair);
            } else {  // arrive
                int chair = available.top();
                available.pop();
                chairMap[friend_] = chair;
                if (friend_ == targetFriend) {
                    return chair;
                }
            }
        }
        
        return -1;
    }
};