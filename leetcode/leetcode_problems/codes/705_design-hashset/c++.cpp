#include <vector>
#include <list>

using namespace std;

class MyHashSet {
private:
    int size = 1000;
    vector<list<int>> buckets;

public:
    MyHashSet() {
        buckets.resize(size);
    }
    
    void add(int key) {
        int index = key % size;
        list<int>& bucket = buckets[index];
        for (int k : bucket) {
            if (k == key) {
                return;
            }
        }
        bucket.push_back(key);
    }
    
    void remove(int key) {
        int index = key % size;
        list<int>& bucket = buckets[index];
        bucket.remove(key);
    }
    
    bool contains(int key) {
        int index = key % size;
        list<int>& bucket = buckets[index];
        for (int k : bucket) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }
};
