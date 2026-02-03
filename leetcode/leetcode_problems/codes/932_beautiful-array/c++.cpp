/*
 * Problem: Beautiful Array
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Divide and conquer - split into odd and even parts, recursively build beautiful arrays
 * Time Complexity: O(n log n)
 * Space Complexity: O(n log n) for recursion stack
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, vector<int>> memo;
    
    vector<int> f(int N) {
        if (memo.find(N) == memo.end()) {
            if (N == 1) {
                memo[1] = {1};
            } else {
                vector<int> odds, evens;
                for (int x : f((N + 1) / 2)) {
                    odds.push_back(2 * x - 1);
                }
                for (int x : f(N / 2)) {
                    evens.push_back(2 * x);
                }
                odds.insert(odds.end(), evens.begin(), evens.end());
                memo[N] = odds;
            }
        }
        return memo[N];
    }
    
public:
    vector<int> beautifulArray(int n) {
        return f(n);
    }
};