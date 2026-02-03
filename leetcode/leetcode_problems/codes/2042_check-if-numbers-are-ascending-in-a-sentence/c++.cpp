/*
 * Problem: Check if Numbers Are Ascending in a Sentence
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Extract all numbers, check if they form strictly increasing sequence
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(k) where k is number of numbers
 */

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    bool areNumbersAscending(string s) {
        vector<int> numbers;
        stringstream ss(s);
        string word;
        
        while (ss >> word) {
            bool isNumber = true;
            for (char c : word) {
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber) {
                numbers.push_back(stoi(word));
            }
        }
        
        for (int i = 1; i < numbers.size(); i++) {
            if (numbers[i] <= numbers[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
};