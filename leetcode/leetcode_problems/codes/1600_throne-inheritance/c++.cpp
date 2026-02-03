/*
 * Problem: Throne Inheritance
 * Difficulty: Medium
 * Tags: string, tree, hash, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ThroneInheritance {
private:
    string king;
    unordered_map<string, vector<string>> children;
    unordered_set<string> dead;
    
    void dfs(string name, vector<string>& result) {
        if (dead.find(name) == dead.end()) {
            result.push_back(name);
        }
        if (children.find(name) != children.end()) {
            for (string& child : children[name]) {
                dfs(child, result);
            }
        }
    }
    
public:
    ThroneInheritance(string kingName) {
        king = kingName;
    }
    
    void birth(string parentName, string childName) {
        children[parentName].push_back(childName);
    }
    
    void death(string name) {
        dead.insert(name);
    }
    
    vector<string> getInheritanceOrder() {
        vector<string> result;
        dfs(king, result);
        return result;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */