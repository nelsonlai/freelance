/*
 * Problem: Count The Repetitions
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        if (s2.empty()) {
            return 0;
        }
        
        int s1Count = 0;
        int s2Count = 0;
        int index = 0;
        unordered_map<int, pair<int, int>> recall;
        
        while (s1Count < n1) {
            for (char c : s1) {
                if (c == s2[index]) {
                    index++;
                    if (index == s2.length()) {
                        s2Count++;
                        index = 0;
                    }
                }
            }
            
            s1Count++;
            
            if (recall.find(index) != recall.end()) {
                auto prev = recall[index];
                int cycleS1 = s1Count - prev.first;
                int cycleS2 = s2Count - prev.second;
                int remainingCycles = (n1 - s1Count) / cycleS1;
                s1Count += remainingCycles * cycleS1;
                s2Count += remainingCycles * cycleS2;
            } else {
                recall[index] = {s1Count, s2Count};
            }
        }
        
        return s2Count / n2;
    }
};