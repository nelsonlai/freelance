/*
 * Problem: Operations on Tree
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Tree with locking mechanism - check ancestors and descendants
 * Time Complexity: O(n) for unlock, O(h) for lock where h is height
 * Space Complexity: O(n)
 */

#include <vector>
#include <unordered_map>

using namespace std;

class LockingTree {
private:
    vector<int> parent;
    unordered_map<int, int> locked;
    unordered_map<int, vector<int>> children;
    
    bool hasLockedDescendant(int node) {
        if (locked.find(node) != locked.end()) {
            return true;
        }
        for (int child : children[node]) {
            if (hasLockedDescendant(child)) {
                return true;
            }
        }
        return false;
    }
    
    void unlockDescendants(int node) {
        locked.erase(node);
        for (int child : children[node]) {
            unlockDescendants(child);
        }
    }
    
public:
    LockingTree(vector<int>& parent) : parent(parent) {
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                children[parent[i]].push_back(i);
            }
        }
    }
    
    bool lock(int num, int user) {
        if (locked.find(num) != locked.end()) {
            return false;
        }
        locked[num] = user;
        return true;
    }
    
    bool unlock(int num, int user) {
        if (locked.find(num) == locked.end() || locked[num] != user) {
            return false;
        }
        locked.erase(num);
        return true;
    }
    
    bool upgrade(int num, int user) {
        if (locked.find(num) != locked.end()) {
            return false;
        }
        
        // Check if any ancestor is locked
        int node = num;
        while (node != -1) {
            if (locked.find(node) != locked.end()) {
                return false;
            }
            node = parent[node];
        }
        
        // Check if any descendant is locked
        if (!hasLockedDescendant(num)) {
            return false;
        }
        
        // Unlock all descendants
        unlockDescendants(num);
        locked[num] = user;
        return true;
    }
};
