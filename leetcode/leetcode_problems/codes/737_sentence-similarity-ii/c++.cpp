#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    bool dfs(string word1, string word2, unordered_map<string, unordered_set<string>>& graph, unordered_set<string>& visited) {
        if (word1 == word2) {
            return true;
        }
        visited.insert(word1);
        for (string neighbor : graph[word1]) {
            if (visited.find(neighbor) == visited.end() && dfs(neighbor, word2, graph, visited)) {
                return true;
            }
        }
        return false;
    }

public:
    bool areSentencesSimilarTwo(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if (sentence1.size() != sentence2.size()) {
            return false;
        }
        
        unordered_map<string, unordered_set<string>> graph;
        for (auto& pair : similarPairs) {
            graph[pair[0]].insert(pair[1]);
            graph[pair[1]].insert(pair[0]);
        }
        
        for (int i = 0; i < sentence1.size(); i++) {
            if (sentence1[i] != sentence2[i] && !dfs(sentence1[i], sentence2[i], graph, unordered_set<string>())) {
                return false;
            }
        }
        
        return true;
    }
};
