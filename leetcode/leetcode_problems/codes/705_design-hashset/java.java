import java.util.*;

class MyHashSet {
    private int size = 1000;
    private List<List<Integer>> buckets;

    public MyHashSet() {
        buckets = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            buckets.add(new ArrayList<>());
        }
    }
    
    public void add(int key) {
        int index = key % size;
        List<Integer> bucket = buckets.get(index);
        if (!bucket.contains(key)) {
            bucket.add(key);
        }
    }
    
    public void remove(int key) {
        int index = key % size;
        List<Integer> bucket = buckets.get(index);
        bucket.removeIf(k -> k == key);
    }
    
    public boolean contains(int key) {
        int index = key % size;
        List<Integer> bucket = buckets.get(index);
        return bucket.contains(key);
    }
}
