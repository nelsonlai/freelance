/*
 * Problem: Time Needed to Buy Tickets
 * Difficulty: Easy
 * Tags: array, simulation
 * 
 * Approach: Calculate time needed for person k to buy all tickets
 * Time Complexity: O(n) where n is array length
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int time = 0;
        int target = tickets[k];
        
        for (int i = 0; i < tickets.size(); i++) {
            if (i < k) {
                // People before k: buy min(tickets[i], target) tickets
                time += min(tickets[i], target);
            } else if (i == k) {
                // Person k: buy target tickets
                time += target;
            } else {
                // People after k: buy min(tickets[i], target - 1) tickets
                time += min(tickets[i], target - 1);
            }
        }
        
        return time;
    }
};