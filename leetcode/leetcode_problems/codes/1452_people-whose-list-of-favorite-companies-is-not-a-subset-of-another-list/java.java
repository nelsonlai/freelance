/**
 * Problem: People Whose List of Favorite Companies Is Not a Subset of Another List
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Convert to sets, check if each list is subset of any other
 * Time Complexity: O(n^2 * m) where n is people, m is companies
 * Space Complexity: O(n * m) for sets
 */

import java.util.*;

class Solution {
    public List<Integer> peopleIndexes(List<List<String>> favoriteCompanies) {
        List<Set<String>> sets = new ArrayList<>();
        for (List<String> companies : favoriteCompanies) {
            sets.add(new HashSet<>(companies));
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < sets.size(); i++) {
            boolean isSubset = false;
            for (int j = 0; j < sets.size(); j++) {
                if (i != j && sets.get(j).containsAll(sets.get(i))) {
                    isSubset = true;
                    break;
                }
            }
            if (!isSubset) {
                result.add(i);
            }
        }
        
        return result;
    }
}