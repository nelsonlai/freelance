/**
 * ADVANCED LEVEL - Lesson 2: Collections Framework
 * 
 * This lesson covers:
 * - List (ArrayList, LinkedList)
 * - Set (HashSet, TreeSet, LinkedHashSet)
 * - Map (HashMap, TreeMap, LinkedHashMap)
 * - Queue and Deque
 * - Iterator and ListIterator
 * - Collections utility class
 */

import java.util.*;

public class CollectionsExample {
    public static void main(String[] args) {
        System.out.println("=== LIST INTERFACE ===");
        
        // ArrayList - Dynamic array, fast random access
        List<String> arrayList = new ArrayList<>();
        arrayList.add("Apple");
        arrayList.add("Banana");
        arrayList.add("Cherry");
        arrayList.add(1, "Apricot");  // Insert at index
        System.out.println("ArrayList: " + arrayList);
        System.out.println("Size: " + arrayList.size());
        System.out.println("Element at index 2: " + arrayList.get(2));
        
        // LinkedList - Doubly linked list, fast insertion/deletion
        List<Integer> linkedList = new LinkedList<>();
        linkedList.add(10);
        linkedList.add(20);
        linkedList.add(30);
        linkedList.addFirst(5);   // Add at beginning
        linkedList.addLast(40);   // Add at end
        System.out.println("LinkedList: " + linkedList);
        
        System.out.println("\n=== SET INTERFACE ===");
        
        // HashSet - No order, no duplicates, O(1) operations
        Set<String> hashSet = new HashSet<>();
        hashSet.add("Red");
        hashSet.add("Green");
        hashSet.add("Blue");
        hashSet.add("Red");  // Duplicate, will be ignored
        System.out.println("HashSet: " + hashSet);
        System.out.println("Contains 'Red': " + hashSet.contains("Red"));
        
        // TreeSet - Sorted order, no duplicates, O(log n) operations
        Set<Integer> treeSet = new TreeSet<>();
        treeSet.add(30);
        treeSet.add(10);
        treeSet.add(20);
        treeSet.add(5);
        System.out.println("TreeSet (sorted): " + treeSet);
        
        // LinkedHashSet - Insertion order, no duplicates
        Set<String> linkedHashSet = new LinkedHashSet<>();
        linkedHashSet.add("First");
        linkedHashSet.add("Second");
        linkedHashSet.add("Third");
        System.out.println("LinkedHashSet (insertion order): " + linkedHashSet);
        
        System.out.println("\n=== MAP INTERFACE ===");
        
        // HashMap - Key-value pairs, no order, O(1) operations
        Map<String, Integer> hashMap = new HashMap<>();
        hashMap.put("Alice", 25);
        hashMap.put("Bob", 30);
        hashMap.put("Charlie", 28);
        hashMap.put("Alice", 26);  // Updates existing key
        System.out.println("HashMap: " + hashMap);
        System.out.println("Alice's age: " + hashMap.get("Alice"));
        System.out.println("Contains key 'Bob': " + hashMap.containsKey("Bob"));
        
        // TreeMap - Sorted by keys
        Map<String, Integer> treeMap = new TreeMap<>();
        treeMap.put("Zebra", 100);
        treeMap.put("Apple", 50);
        treeMap.put("Banana", 75);
        System.out.println("TreeMap (sorted by key): " + treeMap);
        
        // LinkedHashMap - Insertion order
        Map<String, Integer> linkedHashMap = new LinkedHashMap<>();
        linkedHashMap.put("First", 1);
        linkedHashMap.put("Second", 2);
        linkedHashMap.put("Third", 3);
        System.out.println("LinkedHashMap (insertion order): " + linkedHashMap);
        
        System.out.println("\n=== QUEUE INTERFACE ===");
        
        // PriorityQueue - Natural ordering or custom comparator
        Queue<Integer> priorityQueue = new PriorityQueue<>();
        priorityQueue.offer(30);
        priorityQueue.offer(10);
        priorityQueue.offer(20);
        priorityQueue.offer(5);
        System.out.print("PriorityQueue (removed in order): ");
        while (!priorityQueue.isEmpty()) {
            System.out.print(priorityQueue.poll() + " ");
        }
        System.out.println();
        
        // Deque - Double-ended queue
        Deque<String> deque = new ArrayDeque<>();
        deque.addFirst("First");
        deque.addLast("Last");
        deque.offerFirst("Before First");
        deque.offerLast("After Last");
        System.out.println("Deque: " + deque);
        System.out.println("Remove first: " + deque.removeFirst());
        System.out.println("Remove last: " + deque.removeLast());
        
        System.out.println("\n=== ITERATORS ===");
        
        List<String> fruits = new ArrayList<>(Arrays.asList("Apple", "Banana", "Cherry"));
        
        // Iterator
        System.out.print("Using Iterator: ");
        Iterator<String> iterator = fruits.iterator();
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();
        
        // Enhanced for loop (uses iterator internally)
        System.out.print("Using enhanced for: ");
        for (String fruit : fruits) {
            System.out.print(fruit + " ");
        }
        System.out.println();
        
        // ListIterator - Can iterate in both directions
        ListIterator<String> listIterator = fruits.listIterator();
        System.out.print("Forward: ");
        while (listIterator.hasNext()) {
            System.out.print(listIterator.next() + " ");
        }
        System.out.print("\nBackward: ");
        while (listIterator.hasPrevious()) {
            System.out.print(listIterator.previous() + " ");
        }
        System.out.println();
        
        System.out.println("\n=== COLLECTIONS UTILITY CLASS ===");
        
        List<Integer> numbers = new ArrayList<>(Arrays.asList(5, 2, 8, 1, 9, 3));
        System.out.println("Original: " + numbers);
        
        Collections.sort(numbers);
        System.out.println("Sorted: " + numbers);
        
        Collections.reverse(numbers);
        System.out.println("Reversed: " + numbers);
        
        Collections.shuffle(numbers);
        System.out.println("Shuffled: " + numbers);
        
        System.out.println("Max: " + Collections.max(numbers));
        System.out.println("Min: " + Collections.min(numbers));
        
        Collections.fill(numbers, 0);
        System.out.println("Filled with 0: " + numbers);
        
        System.out.println("\n=== ITERATING MAPS ===");
        
        Map<String, Integer> ages = new HashMap<>();
        ages.put("Alice", 25);
        ages.put("Bob", 30);
        ages.put("Charlie", 28);
        
        // Iterate keys
        System.out.print("Keys: ");
        for (String key : ages.keySet()) {
            System.out.print(key + " ");
        }
        System.out.println();
        
        // Iterate values
        System.out.print("Values: ");
        for (Integer value : ages.values()) {
            System.out.print(value + " ");
        }
        System.out.println();
        
        // Iterate entries
        System.out.println("Entries:");
        for (Map.Entry<String, Integer> entry : ages.entrySet()) {
            System.out.println("  " + entry.getKey() + " -> " + entry.getValue());
        }
        
        System.out.println("\n=== CONVERTING BETWEEN COLLECTIONS ===");
        
        // Array to List
        String[] array = {"One", "Two", "Three"};
        List<String> listFromArray = Arrays.asList(array);
        System.out.println("List from array: " + listFromArray);
        
        // List to Array
        List<String> list = new ArrayList<>(Arrays.asList("A", "B", "C"));
        String[] arrayFromList = list.toArray(new String[0]);
        System.out.print("Array from list: ");
        for (String s : arrayFromList) {
            System.out.print(s + " ");
        }
        System.out.println();
        
        // Set from List (removes duplicates)
        List<Integer> withDuplicates = Arrays.asList(1, 2, 2, 3, 3, 3, 4);
        Set<Integer> uniqueSet = new HashSet<>(withDuplicates);
        System.out.println("List with duplicates: " + withDuplicates);
        System.out.println("Set (unique): " + uniqueSet);
    }
}

