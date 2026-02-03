/*
 * Problem: Longest Common Subpath
 * Difficulty: Hard
 * Tags: array, hash, search, rolling hash, binary search
 * 
 * Approach: Binary search on length, use rolling hash to check if subpath exists in all paths
 * Time Complexity: O(m * L * log(min_path_length)) where m is paths, L is avg path length
 * Space Complexity: O(L)
 */

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    static constexpr long long MOD1 = 1000000007;
    static constexpr long long MOD2 = 1000000009;
    static constexpr long long BASE1 = 100001;
    static constexpr long long BASE2 = 100003;
    
    bool check(vector<vector<int>>& paths, int length) {
        if (length == 0) return true;
        
        unordered_set<long long> hashSet;
        long long hash1 = 0, hash2 = 0;
        long long pow1 = 1, pow2 = 1;
        
        // First path
        for (int i = 0; i < paths[0].size(); i++) {
            hash1 = (hash1 * BASE1 + paths[0][i]) % MOD1;
            hash2 = (hash2 * BASE2 + paths[0][i]) % MOD2;
            
            if (i >= length - 1) {
                if (i >= length) {
                    hash1 = (hash1 - paths[0][i - length] * pow1 % MOD1 + MOD1) % MOD1;
                    hash2 = (hash2 - paths[0][i - length] * pow2 % MOD2 + MOD2) % MOD2;
                }
                hashSet.insert(hash1 * MOD2 + hash2);
            }
            
            if (i < length - 1) {
                pow1 = (pow1 * BASE1) % MOD1;
                pow2 = (pow2 * BASE2) % MOD2;
            }
        }
        
        // Check other paths
        for (int p = 1; p < paths.size(); p++) {
            unordered_set<long long> tempSet;
            hash1 = 0;
            hash2 = 0;
            pow1 = 1;
            pow2 = 1;
            
            for (int i = 0; i < paths[p].size(); i++) {
                hash1 = (hash1 * BASE1 + paths[p][i]) % MOD1;
                hash2 = (hash2 * BASE2 + paths[p][i]) % MOD2;
                
                if (i >= length - 1) {
                    if (i >= length) {
                        hash1 = (hash1 - paths[p][i - length] * pow1 % MOD1 + MOD1) % MOD1;
                        hash2 = (hash2 - paths[p][i - length] * pow2 % MOD2 + MOD2) % MOD2;
                    }
                    long long hash = hash1 * MOD2 + hash2;
                    if (hashSet.find(hash) != hashSet.end()) {
                        tempSet.insert(hash);
                    }
                }
                
                if (i < length - 1) {
                    pow1 = (pow1 * BASE1) % MOD1;
                    pow2 = (pow2 * BASE2) % MOD2;
                }
            }
            
            if (tempSet.empty()) {
                return false;
            }
            hashSet = tempSet;
        }
        
        return true;
    }
    
public:
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        int minLen = INT_MAX;
        for (auto& path : paths) {
            minLen = min(minLen, (int)path.size());
        }
        
        int left = 0, right = minLen;
        int result = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(paths, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};