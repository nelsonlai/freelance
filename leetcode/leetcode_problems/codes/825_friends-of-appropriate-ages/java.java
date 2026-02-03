import java.util.*;

class Solution {
    public int numFriendRequests(int[] ages) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int age : ages) {
            count.put(age, count.getOrDefault(age, 0) + 1);
        }
        
        int result = 0;
        for (Map.Entry<Integer, Integer> entryA : count.entrySet()) {
            int ageA = entryA.getKey();
            int countA = entryA.getValue();
            for (Map.Entry<Integer, Integer> entryB : count.entrySet()) {
                int ageB = entryB.getKey();
                int countB = entryB.getValue();
                if (ageB <= 0.5 * ageA + 7 || ageB > ageA || (ageB > 100 && ageA < 100)) {
                    continue;
                }
                result += countA * countB;
                if (ageA == ageB) {
                    result -= countA;
                }
            }
        }
        return result;
    }
}
