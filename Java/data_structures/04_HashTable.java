/**
 * DATA STRUCTURES - Lesson 4: Hash Table
 * 
 * This lesson covers:
 * - Hash Table implementation
 * - Hash functions
 * - Collision handling (Chaining, Linear Probing)
 * - Hash Map operations
 */

import java.util.*;

// ========== HASH TABLE WITH CHAINING ==========

class HashNode {
    String key;
    Integer value;
    HashNode next;
    
    public HashNode(String key, Integer value) {
        this.key = key;
        this.value = value;
        this.next = null;
    }
}

class HashTable {
    private HashNode[] buckets;
    private int capacity;
    private int size;
    
    public HashTable(int capacity) {
        this.capacity = capacity;
        this.buckets = new HashNode[capacity];
        this.size = 0;
    }
    
    // Hash function
    private int hash(String key) {
        int hashCode = key.hashCode();
        return Math.abs(hashCode) % capacity;
    }
    
    // Insert key-value pair
    public void put(String key, Integer value) {
        int index = hash(key);
        HashNode head = buckets[index];
        
        // Check if key already exists
        while (head != null) {
            if (head.key.equals(key)) {
                head.value = value;  // Update existing
                return;
            }
            head = head.next;
        }
        
        // Insert new node at beginning
        HashNode newNode = new HashNode(key, value);
        newNode.next = buckets[index];
        buckets[index] = newNode;
        size++;
    }
    
    // Get value by key
    public Integer get(String key) {
        int index = hash(key);
        HashNode head = buckets[index];
        
        while (head != null) {
            if (head.key.equals(key)) {
                return head.value;
            }
            head = head.next;
        }
        return null;
    }
    
    // Remove key-value pair
    public Integer remove(String key) {
        int index = hash(key);
        HashNode head = buckets[index];
        HashNode prev = null;
        
        while (head != null) {
            if (head.key.equals(key)) {
                if (prev == null) {
                    buckets[index] = head.next;
                } else {
                    prev.next = head.next;
                }
                size--;
                return head.value;
            }
            prev = head;
            head = head.next;
        }
        return null;
    }
    
    // Check if key exists
    public boolean containsKey(String key) {
        return get(key) != null;
    }
    
    // Get size
    public int size() {
        return size;
    }
    
    // Display hash table
    public void display() {
        for (int i = 0; i < capacity; i++) {
            System.out.print("Bucket " + i + ": ");
            HashNode head = buckets[i];
            while (head != null) {
                System.out.print("[" + head.key + "=" + head.value + "] -> ");
                head = head.next;
            }
            System.out.println("null");
        }
    }
}

// ========== HASH TABLE WITH LINEAR PROBING ==========

class HashEntry {
    String key;
    Integer value;
    boolean isDeleted;
    
    public HashEntry(String key, Integer value) {
        this.key = key;
        this.value = value;
        this.isDeleted = false;
    }
}

class LinearProbingHashTable {
    private HashEntry[] table;
    private int capacity;
    private int size;
    
    public LinearProbingHashTable(int capacity) {
        this.capacity = capacity;
        this.table = new HashEntry[capacity];
        this.size = 0;
    }
    
    private int hash(String key) {
        int hashCode = key.hashCode();
        return Math.abs(hashCode) % capacity;
    }
    
    public void put(String key, Integer value) {
        if (size >= capacity) {
            System.out.println("Hash table is full!");
            return;
        }
        
        int index = hash(key);
        
        // Find next available slot
        while (table[index] != null && !table[index].isDeleted) {
            if (table[index].key.equals(key)) {
                table[index].value = value;  // Update existing
                return;
            }
            index = (index + 1) % capacity;
        }
        
        table[index] = new HashEntry(key, value);
        size++;
    }
    
    public Integer get(String key) {
        int index = hash(key);
        int startIndex = index;
        
        while (table[index] != null) {
            if (!table[index].isDeleted && table[index].key.equals(key)) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break;  // Wrapped around
        }
        return null;
    }
    
    public Integer remove(String key) {
        int index = hash(key);
        int startIndex = index;
        
        while (table[index] != null) {
            if (!table[index].isDeleted && table[index].key.equals(key)) {
                table[index].isDeleted = true;
                size--;
                return table[index].value;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break;
        }
        return null;
    }
    
    public boolean containsKey(String key) {
        return get(key) != null;
    }
    
    public int size() {
        return size;
    }
    
    public void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != null && !table[i].isDeleted) {
                System.out.println("Index " + i + ": [" + table[i].key + "=" + table[i].value + "]");
            }
        }
    }
}

// ========== MAIN CLASS ==========

public class HashTable {
    public static void main(String[] args) {
        System.out.println("=== HASH TABLE WITH CHAINING ===");
        
        HashTable hashTable = new HashTable(10);
        hashTable.put("apple", 1);
        hashTable.put("banana", 2);
        hashTable.put("cherry", 3);
        hashTable.put("date", 4);
        hashTable.put("elderberry", 5);
        
        System.out.println("\nHash Table Structure:");
        hashTable.display();
        
        System.out.println("\nGet 'banana': " + hashTable.get("banana"));
        System.out.println("Get 'grape': " + hashTable.get("grape"));
        System.out.println("Contains 'cherry': " + hashTable.containsKey("cherry"));
        
        System.out.println("\nRemoving 'banana'...");
        hashTable.remove("banana");
        hashTable.display();
        
        System.out.println("\nSize: " + hashTable.size());
        
        System.out.println("\n=== HASH TABLE WITH LINEAR PROBING ===");
        
        LinearProbingHashTable lpHashTable = new LinearProbingHashTable(10);
        lpHashTable.put("one", 1);
        lpHashTable.put("two", 2);
        lpHashTable.put("three", 3);
        lpHashTable.put("four", 4);
        
        System.out.println("\nHash Table:");
        lpHashTable.display();
        
        System.out.println("\nGet 'two': " + lpHashTable.get("two"));
        System.out.println("Get 'five': " + lpHashTable.get("five"));
        
        System.out.println("\nRemoving 'two'...");
        lpHashTable.remove("two");
        lpHashTable.display();
        
        System.out.println("\n=== JAVA'S HASHMAP ===");
        Map<String, Integer> javaHashMap = new HashMap<>();
        javaHashMap.put("Alice", 25);
        javaHashMap.put("Bob", 30);
        javaHashMap.put("Charlie", 28);
        
        System.out.println("HashMap: " + javaHashMap);
        System.out.println("Bob's age: " + javaHashMap.get("Bob"));
        System.out.println("Contains Alice: " + javaHashMap.containsKey("Alice"));
        
        // Iterate
        System.out.println("\nIterating:");
        for (Map.Entry<String, Integer> entry : javaHashMap.entrySet()) {
            System.out.println(entry.getKey() + " -> " + entry.getValue());
        }
    }
}

