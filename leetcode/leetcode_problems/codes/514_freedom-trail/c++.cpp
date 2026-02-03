/*
 * Problem: Freedom Trail
 * Difficulty: Hard
 * Tags: string, dp, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
private:
    unordered_map<string, int> memo;
    
    int dp(int ringPos, int keyPos, string& ring, string& key, unordered_map<char, vector<int>>& charPositions) {
        if (keyPos == key.length()) {
            return 0;
        }
        
        string memoKey = to_string(ringPos) + "," + to_string(keyPos);
        if (memo.find(memoKey) != memo.end()) {
            return memo[memoKey];
        }
        
        int minSteps = INT_MAX;
        char targetChar = key[keyPos];
        
        for (int pos : charPositions[targetChar]) {
            int steps = min(abs(pos - ringPos), (int)ring.length() - abs(pos - ringPos));
            minSteps = min(minSteps, steps + 1 + dp(pos, keyPos + 1, ring, key, charPositions));
        }
        
        memo[memoKey] = minSteps;
        return minSteps;
    }

public:
    int findRotateSteps(string ring, string key) {
        unordered_map<char, vector<int>> charPositions;
        for (int i = 0; i < ring.length(); i++) {
            charPositions[ring[i]].push_back(i);
        }
        return dp(0, 0, ring, key, charPositions);
    }
};