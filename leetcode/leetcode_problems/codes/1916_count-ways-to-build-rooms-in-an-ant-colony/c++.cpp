/*
 * Problem: Count Ways to Build Rooms in an Ant Colony
 * Difficulty: Hard
 * Tags: array, tree, graph, dp, math, combinatorics
 * 
 * Approach: Tree DP with combinatorics - count ways to order children
 * Time Complexity: O(n) where n is rooms
 * Space Complexity: O(n)
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    vector<vector<int>> graph;
    vector<long long> fact;
    vector<long long> invFact;
    
    pair<long long, long long> dfs(int node) {
        long long totalSize = 1;
        long long ways = 1;
        
        vector<pair<long long, long long>> children;
        for (int child : graph[node]) {
            auto childResult = dfs(child);
            children.push_back(childResult);
            totalSize += childResult.first;
        }
        
        long long remaining = totalSize - 1;
        for (auto& child : children) {
            long long childSize = child.first;
            long long childWays = child.second;
            long long comb = nCr(remaining, childSize);
            ways = (ways * comb % MOD * childWays) % MOD;
            remaining -= childSize;
        }
        
        return {totalSize, ways};
    }
    
    long long nCr(long long n, long long r) {
        if (r > n || r < 0) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    }
    
    long long modInverse(long long a, long long m) {
        return power(a, m - 2, m);
    }
    
    long long power(long long base, long long exp, long long mod) {
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
    
public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        int n = prevRoom.size();
        graph.assign(n, vector<int>());
        
        for (int i = 1; i < n; i++) {
            graph[prevRoom[i]].push_back(i);
        }
        
        // Precompute factorials
        fact.assign(n + 1, 1);
        invFact.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
            invFact[i] = modInverse(fact[i], MOD);
        }
        
        auto result = dfs(0);
        return result.second;
    }
};