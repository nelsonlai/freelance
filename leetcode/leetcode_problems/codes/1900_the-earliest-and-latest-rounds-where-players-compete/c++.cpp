/*
 * Problem: The Earliest and Latest Rounds Where Players Compete
 * Difficulty: Hard
 * Tags: array, dp, recursion
 * 
 * Approach: Recursive DP to simulate tournament rounds
 * Time Complexity: O(n^2) where n is players
 * Space Complexity: O(n^2)
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<string, vector<int>> memo;
    
    vector<int> dp(int players, int first, int second) {
        if (first + second == players + 1) {
            return {1, 1};
        }
        
        if (first > second) {
            swap(first, second);
        }
        
        string key = to_string(players) + "," + to_string(first) + "," + to_string(second);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int half = (players + 1) / 2;
        vector<int> result;
        
        if (first + second <= players + 1) {
            result = dp(half, first, second);
        } else {
            int offset = players - half;
            result = dp(half, first - offset, second - offset);
        }
        
        memo[key] = result;
        return result;
    }
    
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        return dp(n, firstPlayer, secondPlayer);
    }
};