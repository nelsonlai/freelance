/*
 * Problem: Kth Distinct String in an Array
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Count occurrences, find kth distinct string
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        unordered_map<string, int> count;
        for (string& s : arr) {
            count[s]++;
        }
        
        int distinctCount = 0;
        for (string& s : arr) {
            if (count[s] == 1) {
                distinctCount++;
                if (distinctCount == k) {
                    return s;
                }
            }
        }
        
        return "";
    }
};