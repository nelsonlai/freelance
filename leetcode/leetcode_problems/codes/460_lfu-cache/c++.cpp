/*
 * Problem: LFU Cache
 * Difficulty: Hard
 * Tags: hash, linked_list
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <list>
#include <map>

using namespace std;

class LFUCache {
private:
    struct Node {
        int key, value, freq;
    };
    
    int capacity;
    int minFreq;
    unordered_map<int, list<Node>::iterator> keyToNode;
    map<int, list<Node>> freqToNodes;

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->minFreq = 0;
    }
    
    int get(int key) {
        if (keyToNode.find(key) == keyToNode.end()) {
            return -1;
        }
        
        auto it = keyToNode[key];
        int value = it->value;
        int freq = it->freq;
        
        freqToNodes[freq].erase(it);
        if (freqToNodes[freq].empty()) {
            freqToNodes.erase(freq);
            if (freq == minFreq) {
                minFreq++;
            }
        }
        
        freq++;
        freqToNodes[freq].push_front({key, value, freq});
        keyToNode[key] = freqToNodes[freq].begin();
        
        return value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }
        
        if (keyToNode.find(key) != keyToNode.end()) {
            auto it = keyToNode[key];
            it->value = value;
            get(key);
            return;
        }
        
        if (keyToNode.size() >= capacity) {
            auto& nodes = freqToNodes[minFreq];
            int lfuKey = nodes.back().key;
            nodes.pop_back();
            if (nodes.empty()) {
                freqToNodes.erase(minFreq);
            }
            keyToNode.erase(lfuKey);
        }
        
        minFreq = 1;
        freqToNodes[1].push_front({key, value, 1});
        keyToNode[key] = freqToNodes[1].begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */