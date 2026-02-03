import java.util.*;

class Solution {
    private int n;
    private Set<Integer> blacklist;
    private List<Integer> whitelist;
    private int m;
    private Map<Integer, Integer> mapping;

    public Solution(int n, int[] blacklist) {
        this.n = n;
        this.blacklist = new HashSet<>();
        for (int num : blacklist) {
            this.blacklist.add(num);
        }
        this.m = n - blacklist.length;
        
        if (blacklist.length < n / 2) {
            this.whitelist = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (!this.blacklist.contains(i)) {
                    this.whitelist.add(i);
                }
            }
        } else {
            this.mapping = new HashMap<>();
            int j = this.m;
            for (int num : blacklist) {
                if (num < this.m) {
                    while (this.blacklist.contains(j)) {
                        j++;
                    }
                    this.mapping.put(num, j);
                    j++;
                }
            }
        }
    }
    
    public int pick() {
        Random rand = new Random();
        if (blacklist.size() < n / 2) {
            return whitelist.get(rand.nextInt(whitelist.size()));
        } else {
            int r = rand.nextInt(m);
            return mapping.getOrDefault(r, r);
        }
    }
}
