/*
 * Problem: Rings and Rods
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int countPoints(string rings) {
        unordered_map<char, unordered_set<char>> rods;
        for (int i = 0; i < rings.length(); i += 2) {
            char color = rings[i];
            char rod = rings[i + 1];
            rods[rod].insert(color);
        }
        
        int count = 0;
        for (auto& entry : rods) {
            if (entry.second.size() == 3) {
                count++;
            }
        }
        return count;
    }
};