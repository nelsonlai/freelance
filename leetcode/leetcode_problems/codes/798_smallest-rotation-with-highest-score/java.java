class Solution {
    public int bestRotation(int[] nums) {
        int n = nums.length;
        int[] bad = new int[n];
        
        for (int i = 0; i < n; i++) {
            int left = (i - nums[i] + 1 + n) % n;
            int right = (i + 1) % n;
            bad[left]--;
            bad[right]++;
            if (left > right) {
                bad[0]--;
            }
        }
        
        int best = -n;
        int result = 0;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            cur += bad[i];
            if (cur > best) {
                best = cur;
                result = i;
            }
        }
        return result;
    }
}
