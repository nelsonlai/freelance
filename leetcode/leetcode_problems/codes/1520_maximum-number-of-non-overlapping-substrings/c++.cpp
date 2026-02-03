/*
 * Problem: Maximum Number of Non-Overlapping Substrings
 * Difficulty: Hard
 * Tags: string, tree, greedy
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
    pair<int, int> extend(string& s, int start, int end, unordered_map<char, int>& first, unordered_map<char, int>& last) {
        int right = end;
        int i = start;
        while (i <= right) {
            char c = s[i];
            if (first[c] < start) {
                return {-1, -1};
            }
            right = max(right, last[c]);
            i++;
        }
        return {start, right};
    }
    
public:
    vector<string> maxNumOfSubstrings(string s) {
        unordered_map<char, int> first, last;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (first.find(c) == first.end()) {
                first[c] = i;
            }
            last[c] = i;
        }
        
        unordered_set<char> chars(s.begin(), s.end());
        vector<pair<int, int>> intervals;
        
        for (char c : chars) {
            auto interval = extend(s, first[c], last[c], first, last);
            if (interval.first != -1) {
                intervals.push_back(interval);
            }
        }
        
        sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.second != b.second) {
                return a.second < b.second;
            }
            return a.first < b.first;
        });
        
        vector<string> result;
        int prevEnd = -1;
        for (auto& interval : intervals) {
            if (interval.first > prevEnd) {
                result.push_back(s.substr(interval.first, interval.second - interval.first + 1));
                prevEnd = interval.second;
            }
        }
        
        return result;
    }
};