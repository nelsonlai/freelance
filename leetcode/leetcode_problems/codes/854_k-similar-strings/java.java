import java.util.*;

class Solution {
    public int kSimilarity(String s1, String s2) {
        if (s1.equals(s2)) {
            return 0;
        }
        
        Queue<String[]> queue = new LinkedList<>();
        queue.offer(new String[]{s1, "0"});
        Set<String> visited = new HashSet<>();
        visited.add(s1);
        
        while (!queue.isEmpty()) {
            String[] curr = queue.poll();
            String s = curr[0];
            int steps = Integer.parseInt(curr[1]);
            
            if (s.equals(s2)) {
                return steps;
            }
            
            int i = 0;
            while (i < s.length() && s.charAt(i) == s2.charAt(i)) {
                i++;
            }
            
            for (int j = i + 1; j < s.length(); j++) {
                if (s.charAt(j) == s2.charAt(i) && s.charAt(j) != s2.charAt(j)) {
                    String newS = s.substring(0, i) + s.charAt(j) + 
                                 s.substring(i + 1, j) + s.charAt(i) + s.substring(j + 1);
                    if (!visited.contains(newS)) {
                        visited.add(newS);
                        queue.offer(new String[]{newS, String.valueOf(steps + 1)});
                    }
                }
            }
        }
        return -1;
    }
}
