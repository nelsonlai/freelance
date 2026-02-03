class Solution {
    public int longestMountain(int[] arr) {
        int n = arr.length;
        int result = 0;
        int i = 1;
        
        while (i < n) {
            while (i < n && arr[i-1] >= arr[i]) {
                i++;
            }
            int start = i - 1;
            
            while (i < n && arr[i-1] < arr[i]) {
                i++;
            }
            int peak = i - 1;
            
            while (i < n && arr[i-1] > arr[i]) {
                i++;
            }
            int end = i - 1;
            
            if (peak > start && end > peak) {
                result = Math.max(result, end - start + 1);
            }
        }
        
        return result;
    }
}
