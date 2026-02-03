import java.util.*;

class TopVotedCandidate {
    private int[] times;
    private int[] leaders;
    
    public TopVotedCandidate(int[] persons, int[] times) {
        this.times = times;
        this.leaders = new int[persons.length];
        Map<Integer, Integer> count = new HashMap<>();
        int leader = -1;
        
        for (int i = 0; i < persons.length; i++) {
            count.put(persons[i], count.getOrDefault(persons[i], 0) + 1);
            if (count.get(persons[i]) >= count.getOrDefault(leader, 0)) {
                leader = persons[i];
            }
            leaders[i] = leader;
        }
    }
    
    public int q(int t) {
        int idx = Arrays.binarySearch(times, t);
        if (idx < 0) {
            idx = -idx - 2;
        }
        return leaders[idx];
    }
}
