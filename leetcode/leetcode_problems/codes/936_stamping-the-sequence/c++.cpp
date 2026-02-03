/*
 * Problem: Stamping The Sequence
 * Difficulty: Hard
 * Tags: array, string, greedy, stack, queue
 * 
 * Approach: Work backwards - find positions where stamp can be placed, greedily stamp
 * Time Complexity: O(n * m) where n is target length, m is stamp length
 * Space Complexity: O(n) for result and visited array
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool canStamp(const string& stamp, string& target, int pos) {
        bool changed = false;
        for (int i = 0; i < stamp.length(); i++) {
            if (target[pos + i] == '?') {
                continue;
            }
            if (target[pos + i] != stamp[i]) {
                return false;
            }
            changed = true;
        }
        if (changed) {
            for (int i = 0; i < stamp.length(); i++) {
                target[pos + i] = '?';
            }
        }
        return changed;
    }
    
public:
    vector<int> movesToStamp(string stamp, string target) {
        int n = target.length(), m = stamp.length();
        vector<bool> visited(n, false);
        vector<int> result;
        
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i <= n - m; i++) {
                if (!visited[i] && canStamp(stamp, target, i)) {
                    visited[i] = true;
                    result.push_back(i);
                    changed = true;
                }
            }
        }
        
        for (char c : target) {
            if (c != '?') {
                return {};
            }
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};