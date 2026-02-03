class Solution {
    public int maxChunksToSorted(int[] arr) {
        int result = 0;
        int maxVal = 0;
        for (int i = 0; i < arr.length; i++) {
            maxVal = Math.max(maxVal, arr[i]);
            if (maxVal == i) {
                result++;
            }
        }
        return result;
    }
}
