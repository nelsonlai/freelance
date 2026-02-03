/*
 * Problem: Zuma Game
 * Difficulty: Hard
 * Tags: string, dp, search, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    string removeConsecutive(string s) {
        int i = 0;
        while (i < s.length()) {
            int j = i;
            while (j < s.length() && s[j] == s[i]) {
                j++;
            }
            if (j - i >= 3) {
                s = s.substr(0, i) + s.substr(j);
                i = 0;
            } else {
                i = j;
            }
        }
        return s;
    }
    
    int dfs(string board, unordered_map<char, int>& hand) {
        if (board.empty()) {
            return 0;
        }
        if (hand.empty()) {
            return -1;
        }
        
        int result = INT_MAX;
        int i = 0;
        while (i < board.length()) {
            int j = i;
            while (j < board.length() && board[j] == board[i]) {
                j++;
            }
            
            int need = 3 - (j - i);
            char color = board[i];
            if (hand.find(color) != hand.end() && hand[color] >= need) {
                unordered_map<char, int> newHand = hand;
                newHand[color] -= need;
                if (newHand[color] == 0) {
                    newHand.erase(color);
                }
                
                string newBoard = removeConsecutive(board.substr(0, i) + board.substr(j));
                int res = dfs(newBoard, newHand);
                if (res != -1) {
                    result = min(result, res + need);
                }
            }
            i = j;
        }
        
        return result == INT_MAX ? -1 : result;
    }

public:
    int findMinStep(string board, string hand) {
        unordered_map<char, int> handCount;
        for (char c : hand) {
            handCount[c]++;
        }
        return dfs(board, handCount);
    }
};