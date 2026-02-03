/*
 * Problem: Shopping Offers
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class Solution {
private:
    unordered_map<string, int> memo;
    
    string vectorToString(vector<int>& v) {
        stringstream ss;
        for (int i = 0; i < v.size(); i++) {
            if (i > 0) ss << ",";
            ss << v[i];
        }
        return ss.str();
    }
    
    int dfs(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        string key = vectorToString(needs);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int cost = 0;
        for (int i = 0; i < needs.size(); i++) {
            cost += price[i] * needs[i];
        }
        
        for (auto& offer : special) {
            vector<int> newNeeds = needs;
            bool valid = true;
            
            for (int i = 0; i < needs.size(); i++) {
                if (needs[i] < offer[i]) {
                    valid = false;
                    break;
                }
                newNeeds[i] = needs[i] - offer[i];
            }
            
            if (valid) {
                cost = min(cost, offer.back() + dfs(price, special, newNeeds));
            }
        }
        
        memo[key] = cost;
        return cost;
    }

public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return dfs(price, special, needs);
    }
};