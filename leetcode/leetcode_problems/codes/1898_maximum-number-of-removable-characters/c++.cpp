/*
 * Problem: Maximum Number of Removable Characters
 * Difficulty: Medium
 * Tags: array, string, search, binary search
 * 
 * Approach: Binary search on number of removals, check if p is still subsequence
 * Time Complexity: O(k log k) where k is removable length
 * Space Complexity: O(n)
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool canRemove(string& s, string& p, vector<int>& removable, int k) {
        unordered_set<int> removed(removable.begin(), removable.begin() + k);
        int j = 0;
        for (int i = 0; i < s.length() && j < p.length(); i++) {
            if (removed.find(i) != removed.end()) {
                continue;
            }
            if (s[i] == p[j]) {
                j++;
            }
        }
        return j == p.length();
    }
    
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        int left = 0, right = removable.size();
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canRemove(s, p, removable, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};