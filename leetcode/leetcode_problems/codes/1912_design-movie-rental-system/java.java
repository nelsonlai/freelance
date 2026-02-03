/**
 * Problem: Design Movie Rental System
 * Difficulty: Hard
 * Tags: array, hash, sort, search, queue, heap
 * 
 * Approach: Use heaps to track available and rented movies
 * Time Complexity: O(log n) for search, rent, drop; O(k log n) for report
 * Space Complexity: O(n)
 */

import java.util.*;

class MovieRentingSystem {
    private Map<Integer, PriorityQueue<int[]>> available;
    private PriorityQueue<int[]> rented;
    private Map<String, Integer> shopMovie;
    private Set<String> rentedSet;

    public MovieRentingSystem(int n, int[][] entries) {
        available = new HashMap<>();
        rented = new PriorityQueue<>((a, b) -> {
            if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
            if (a[1] != b[1]) return Integer.compare(a[1], b[1]);
            return Integer.compare(a[2], b[2]);
        });
        shopMovie = new HashMap<>();
        rentedSet = new HashSet<>();
        
        for (int[] entry : entries) {
            int shop = entry[0];
            int movie = entry[1];
            int price = entry[2];
            shopMovie.put(shop + "," + movie, price);
            available.computeIfAbsent(movie, k -> new PriorityQueue<>((a, b) -> {
                if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
                return Integer.compare(a[1], b[1]);
            })).offer(new int[]{price, shop});
        }
    }
    
    public List<Integer> search(int movie) {
        List<Integer> result = new ArrayList<>();
        if (!available.containsKey(movie)) {
            return result;
        }
        
        PriorityQueue<int[]> temp = new PriorityQueue<>(available.get(movie));
        List<int[]> toRestore = new ArrayList<>();
        
        while (result.size() < 5 && !temp.isEmpty()) {
            int[] entry = temp.poll();
            String key = entry[1] + "," + movie;
            if (!rentedSet.contains(key)) {
                result.add(entry[1]);
            }
            toRestore.add(entry);
        }
        
        return result;
    }
    
    public void rent(int shop, int movie) {
        String key = shop + "," + movie;
        rentedSet.add(key);
        int price = shopMovie.get(key);
        rented.offer(new int[]{price, shop, movie});
    }
    
    public void drop(int shop, int movie) {
        String key = shop + "," + movie;
        rentedSet.remove(key);
    }
    
    public List<List<Integer>> report() {
        List<List<Integer>> result = new ArrayList<>();
        PriorityQueue<int[]> temp = new PriorityQueue<>(rented);
        List<int[]> toRestore = new ArrayList<>();
        
        while (result.size() < 5 && !temp.isEmpty()) {
            int[] entry = temp.poll();
            String key = entry[1] + "," + entry[2];
            if (rentedSet.contains(key)) {
                result.add(Arrays.asList(entry[1], entry[2]));
            }
            toRestore.add(entry);
        }
        
        return result;
    }
}

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem obj = new MovieRentingSystem(n, entries);
 * List<Integer> param_1 = obj.search(movie);
 * obj.rent(shop,movie);
 * obj.drop(shop,movie);
 * List<List<Integer>> param_4 = obj.report();
 */