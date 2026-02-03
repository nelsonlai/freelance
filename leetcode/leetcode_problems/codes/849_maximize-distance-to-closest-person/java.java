class Solution {
    public int maxDistToClosest(int[] seats) {
        int n = seats.length;
        int result = 0;
        int last = -1;
        
        for (int i = 0; i < n; i++) {
            if (seats[i] == 1) {
                if (last == -1) {
                    result = i;
                } else {
                    result = Math.max(result, (i - last) / 2);
                }
                last = i;
            }
        }
        
        result = Math.max(result, n - 1 - last);
        return result;
    }
}
