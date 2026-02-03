class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int left = 1, right = 0;
        for (int pile : piles) {
            right = Math.max(right, pile);
        }
        
        while (left < right) {
            int mid = (left + right) / 2;
            if (canFinish(piles, h, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
    
    private boolean canFinish(int[] piles, int h, int speed) {
        int time = 0;
        for (int pile : piles) {
            time += (pile + speed - 1) / speed;
        }
        return time <= h;
    }
}
