/*
 * Problem: Shortest Word Distance II
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

class WordDistance {
private:
    unordered_map<string, vector<int>> wordIndices;

public:
    WordDistance(vector<string>& wordsDict) {
        for (int i = 0; i < wordsDict.size(); i++) {
            wordIndices[wordsDict[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        vector<int>& indices1 = wordIndices[word1];
        vector<int>& indices2 = wordIndices[word2];
        
        int i = 0, j = 0;
        int minDistance = INT_MAX;
        
        while (i < indices1.size() && j < indices2.size()) {
            minDistance = min(minDistance, abs(indices1[i] - indices2[j]));
            if (indices1[i] < indices2[j]) {
                i++;
            } else {
                j++;
            }
        }
        
        return minDistance;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */