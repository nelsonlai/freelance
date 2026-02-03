/*
 * Problem: Minimum Genetic Mutation
 * Difficulty: Medium
 * Tags: string, hash, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        if (bankSet.find(endGene) == bankSet.end()) {
            return -1;
        }
        
        queue<string> q;
        unordered_set<string> visited;
        q.push(startGene);
        visited.insert(startGene);
        vector<char> chars = {'A', 'C', 'G', 'T'};
        int mutations = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string gene = q.front();
                q.pop();
                
                if (gene == endGene) {
                    return mutations;
                }
                
                for (int j = 0; j < gene.length(); j++) {
                    char original = gene[j];
                    for (char c : chars) {
                        if (c != original) {
                            gene[j] = c;
                            if (bankSet.find(gene) != bankSet.end() && visited.find(gene) == visited.end()) {
                                visited.insert(gene);
                                q.push(gene);
                            }
                        }
                    }
                    gene[j] = original;
                }
            }
            mutations++;
        }
        
        return -1;
    }
};