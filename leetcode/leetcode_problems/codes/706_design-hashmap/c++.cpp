#include <vector>
#include <list>
#include <utility>

using namespace std;

class MyHashMap {
private:
    int size = 1000;
    vector<list<pair<int, int>>> buckets;

public:
    MyHashMap() {
        buckets.resize(size);
    }
    
    void put(int key, int value) {
        int index = key % size;
        list<pair<int, int>>& bucket = buckets[index];
        for (auto& p : bucket) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        bucket.push_back({key, value});
    }
    
    int get(int key) {
        int index = key % size;
        list<pair<int, int>>& bucket = buckets[index];
        for (auto& p : bucket) {
            if (p.first == key) {
                return p.second;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        int index = key % size;
        list<pair<int, int>>& bucket = buckets[index];
        bucket.remove_if([key](const pair<int, int>& p) {
            return p.first == key;
        });
    }
};
