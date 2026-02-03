/*
 * Problem: Can Convert String in K Moves
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        if (s.length() != t.length()) {
            return false;
        }
        
        unordered_map<int, int> shifts;
        for (int i = 0; i < s.length(); i++) {
            int shift = ((t[i] - s[i]) % 26 + 26) % 26;
            if (shift > 0) {
                shifts[shift]++;
            }
        }
        
        for (auto& [shift, count] : shifts) {
            int maxShift = shift + 26 * (count - 1);
            if (maxShift > k) {
                return false;
            }
        }
        
        return true;
    }
};