/**
 * Problem: Operations on Tree
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Tree with locking mechanism - check ancestors and descendants
 * Time Complexity: O(n) for unlock, O(h) for lock where h is height
 * Space Complexity: O(n)
 */

import java.util.*;

class LockingTree {
    private int[] parent;
    private Map<Integer, Integer> locked;
    private Map<Integer, List<Integer>> children;
    
    public LockingTree(int[] parent) {
        this.parent = parent;
        this.locked = new HashMap<>();
        this.children = new HashMap<>();
        
        for (int i = 0; i < parent.length; i++) {
            if (parent[i] != -1) {
                children.computeIfAbsent(parent[i], k -> new ArrayList<>()).add(i);
            }
        }
    }
    
    public boolean lock(int num, int user) {
        if (locked.containsKey(num)) {
            return false;
        }
        locked.put(num, user);
        return true;
    }
    
    public boolean unlock(int num, int user) {
        if (!locked.containsKey(num) || locked.get(num) != user) {
            return false;
        }
        locked.remove(num);
        return true;
    }
    
    public boolean upgrade(int num, int user) {
        if (locked.containsKey(num)) {
            return false;
        }
        
        // Check if any ancestor is locked
        int node = num;
        while (node != -1) {
            if (locked.containsKey(node)) {
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
        locked.put(num, user);
        return true;
    }
    
    private boolean hasLockedDescendant(int node) {
        if (locked.containsKey(node)) {
            return true;
        }
        for (int child : children.getOrDefault(node, new ArrayList<>())) {
            if (hasLockedDescendant(child)) {
                return true;
            }
        }
        return false;
    }
    
    private void unlockDescendants(int node) {
        locked.remove(node);
        for (int child : children.getOrDefault(node, new ArrayList<>())) {
            unlockDescendants(child);
        }
    }
}
