import java.util.*;

class MyHashMap {
    private int size = 1000;
    private List<List<int[]>> buckets;

    public MyHashMap() {
        buckets = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            buckets.add(new ArrayList<>());
        }
    }
    
    public void put(int key, int value) {
        int index = key % size;
        List<int[]> bucket = buckets.get(index);
        for (int[] pair : bucket) {
            if (pair[0] == key) {
                pair[1] = value;
                return;
            }
        }
        bucket.add(new int[]{key, value});
    }
    
    public int get(int key) {
        int index = key % size;
        List<int[]> bucket = buckets.get(index);
        for (int[] pair : bucket) {
            if (pair[0] == key) {
                return pair[1];
            }
        }
        return -1;
    }
    
    public void remove(int key) {
        int index = key % size;
        List<int[]> bucket = buckets.get(index);
        bucket.removeIf(pair -> pair[0] == key);
    }
}
