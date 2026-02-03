/*
 * Problem: People Whose List of Favorite Companies Is Not a Subset of Another List
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Convert to sets, check if each list is subset of any other
 * Time Complexity: O(n^2 * m) where n is people, m is companies
 * Space Complexity: O(n * m) for sets
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        vector<unordered_set<string>> sets;
        for (auto& companies : favoriteCompanies) {
            sets.push_back(unordered_set<string>(companies.begin(), companies.end()));
        }
        
        vector<int> result;
        for (int i = 0; i < sets.size(); i++) {
            bool isSubset = false;
            for (int j = 0; j < sets.size(); j++) {
                if (i != j) {
                    bool allFound = true;
                    for (const string& company : favoriteCompanies[i]) {
                        if (sets[j].find(company) == sets[j].end()) {
                            allFound = false;
                            break;
                        }
                    }
                    if (allFound) {
                        isSubset = true;
                        break;
                    }
                }
            }
            if (!isSubset) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};