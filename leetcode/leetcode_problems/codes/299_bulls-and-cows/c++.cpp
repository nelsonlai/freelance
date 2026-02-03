/*
 * Problem: Bulls and Cows
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0;
        int cows = 0;
        
        unordered_map<char, int> secretCount;
        unordered_map<char, int> guessCount;
        
        for (int i = 0; i < secret.length(); i++) {
            if (secret[i] == guess[i]) {
                bulls++;
            } else {
                secretCount[secret[i]]++;
                guessCount[guess[i]]++;
            }
        }
        
        for (auto& pair : secretCount) {
            if (guessCount.find(pair.first) != guessCount.end()) {
                cows += min(pair.second, guessCount[pair.first]);
            }
        }
        
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};