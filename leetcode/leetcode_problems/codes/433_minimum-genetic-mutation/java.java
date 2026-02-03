/**
 * Problem: Minimum Genetic Mutation
 * Difficulty: Medium
 * Tags: string, hash, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int minMutation(String startGene, String endGene, String[] bank) {
        Set<String> bankSet = new HashSet<>(Arrays.asList(bank));
        if (!bankSet.contains(endGene)) {
            return -1;
        }
        
        Queue<String> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.offer(startGene);
        visited.add(startGene);
        char[] chars = {'A', 'C', 'G', 'T'};
        int mutations = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String gene = queue.poll();
                if (gene.equals(endGene)) {
                    return mutations;
                }
                
                char[] geneArray = gene.toCharArray();
                for (int j = 0; j < geneArray.length; j++) {
                    char original = geneArray[j];
                    for (char c : chars) {
                        if (c != original) {
                            geneArray[j] = c;
                            String newGene = new String(geneArray);
                            if (bankSet.contains(newGene) && !visited.contains(newGene)) {
                                visited.add(newGene);
                                queue.offer(newGene);
                            }
                        }
                    }
                    geneArray[j] = original;
                }
            }
            mutations++;
        }
        
        return -1;
    }
}