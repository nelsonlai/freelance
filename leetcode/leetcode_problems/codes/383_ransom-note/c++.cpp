/*
 * Problem: Ransom Note
 * Difficulty: Easy
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
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> magazineCount;
        for (char c : magazine) {
            magazineCount[c]++;
        }
        
        for (char c : ransomNote) {
            if (magazineCount[c] == 0) {
                return false;
            }
            magazineCount[c]--;
        }
        
        return true;
    }
};