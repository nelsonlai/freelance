/**
 * Problem: Word Ladder II
 * Difficulty: Hard
 * Tags: string, hash, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
        List<List<String>> result = new ArrayList<>();
        Set<String> wordSet = new HashSet<>(wordList);
        if (!wordSet.contains(endWord)) {
            return result;
        }
        
        wordSet.add(beginWord);
        Map<String, List<String>> neighbors = new HashMap<>();
        for (String word : wordSet) {
            for (int i = 0; i < word.length(); i++) {
                String pattern = word.substring(0, i) + "*" + word.substring(i + 1);
                neighbors.computeIfAbsent(pattern, k -> new ArrayList<>()).add(word);
            }
        }
        
        Map<String, Integer> distance = new HashMap<>();
        Map<String, List<String>> parents = new HashMap<>();
        Queue<String> queue = new LinkedList<>();
        queue.offer(beginWord);
        distance.put(beginWord, 0);
        boolean found = false;
        
        while (!queue.isEmpty() && !found) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String word = queue.poll();
                for (int j = 0; j < word.length(); j++) {
                    String pattern = word.substring(0, j) + "*" + word.substring(j + 1);
                    for (String neighbor : neighbors.getOrDefault(pattern, new ArrayList<>())) {
                        if (!distance.containsKey(neighbor)) {
                            distance.put(neighbor, distance.get(word) + 1);
                            parents.put(neighbor, new ArrayList<>());
                            parents.get(neighbor).add(word);
                            queue.offer(neighbor);
                        } else if (distance.get(neighbor) == distance.get(word) + 1) {
                            parents.get(neighbor).add(word);
                        }
                        if (neighbor.equals(endWord)) {
                            found = true;
                        }
                    }
                }
            }
        }
        
        if (found) {
            backtrack(endWord, beginWord, new ArrayList<>(), parents, result);
        }
        
        return result;
    }
    
    private void backtrack(String word, String beginWord, List<String> path, 
                          Map<String, List<String>> parents, List<List<String>> result) {
        path.add(word);
        if (word.equals(beginWord)) {
            List<String> solution = new ArrayList<>(path);
            Collections.reverse(solution);
            result.add(solution);
        } else {
            for (String parent : parents.get(word)) {
                backtrack(parent, beginWord, path, parents, result);
            }
        }
        path.remove(path.size() - 1);
    }
}