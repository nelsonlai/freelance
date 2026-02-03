/*
 * Problem: Flip Game
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generatePossibleNextMoves(string currentState) {
        vector<string> result;
        for (int i = 0; i < (int)currentState.length() - 1; i++) {
            if (currentState[i] == '+' && currentState[i + 1] == '+') {
                result.push_back(currentState.substr(0, i) + "--" + currentState.substr(i + 2));
            }
        }
        return result;
    }
};