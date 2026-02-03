/*
 * Problem: Count All Possible Routes
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
    static const int MOD = 1000000007;
    unordered_map<string, int> memo;
    
    int dp(int city, int remainingFuel, vector<int>& locations, int finish) {
        if (remainingFuel < 0) {
            return 0;
        }
        
        string key = to_string(city) + "," + to_string(remainingFuel);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int result = (city == finish) ? 1 : 0;
        
        for (int nextCity = 0; nextCity < locations.size(); nextCity++) {
            if (nextCity != city) {
                int cost = abs(locations[city] - locations[nextCity]);
                if (cost <= remainingFuel) {
                    result = (result + dp(nextCity, remainingFuel - cost, locations, finish)) % MOD;
                }
            }
        }
        
        memo[key] = result;
        return result;
    }
    
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        memo.clear();
        return dp(start, fuel, locations, finish);
    }
};