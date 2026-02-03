/*
 * Problem: Path Crossing
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    bool isPathCrossing(string path) {
        unordered_set<string> visited;
        visited.insert("0,0");
        int x = 0, y = 0;
        
        for (char direction : path) {
            if (direction == 'N') {
                y++;
            } else if (direction == 'S') {
                y--;
            } else if (direction == 'E') {
                x++;
            } else {
                x--;
            }
            
            string pos = to_string(x) + "," + to_string(y);
            if (visited.find(pos) != visited.end()) {
                return true;
            }
            visited.insert(pos);
        }
        
        return false;
    }
};