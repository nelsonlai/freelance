/**
 * Problem: Display Table of Food Orders in a Restaurant
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Group orders by table, count items per table, format output
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for orders map
 */

import java.util.*;

class Solution {
    public List<List<String>> displayTable(List<List<String>> orders) {
        Map<Integer, Map<String, Integer>> tables = new TreeMap<>();
        Set<String> foods = new TreeSet<>();
        
        for (List<String> order : orders) {
            int table = Integer.parseInt(order.get(1));
            String food = order.get(2);
            tables.computeIfAbsent(table, k -> new HashMap<>()).merge(food, 1, Integer::sum);
            foods.add(food);
        }
        
        List<List<String>> result = new ArrayList<>();
        List<String> header = new ArrayList<>();
        header.add("Table");
        header.addAll(foods);
        result.add(header);
        
        for (Map.Entry<Integer, Map<String, Integer>> entry : tables.entrySet()) {
            List<String> row = new ArrayList<>();
            row.add(String.valueOf(entry.getKey()));
            for (String food : foods) {
                row.add(String.valueOf(entry.getValue().getOrDefault(food, 0)));
            }
            result.add(row);
        }
        
        return result;
    }
}