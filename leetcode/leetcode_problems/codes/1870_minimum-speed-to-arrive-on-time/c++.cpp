/*
 * Problem: Minimum Speed to Arrive on Time
 * Difficulty: Medium
 * Tags: array, search, binary search
 * 
 * Approach: Binary search on speed, check if can arrive on time
 * Time Complexity: O(n log(max_speed)) where max_speed is max distance * 100
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
private:
    bool canArrive(vector<int>& dist, double hour, int speed) {
        double totalTime = 0;
        for (int i = 0; i < dist.size(); i++) {
            if (i < dist.size() - 1) {
                totalTime += ceil((double)dist[i] / speed);
            } else {
                totalTime += (double)dist[i] / speed;
            }
        }
        return totalTime <= hour;
    }
    
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int left = 1, right = 10000000;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canArrive(dist, hour, mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
};