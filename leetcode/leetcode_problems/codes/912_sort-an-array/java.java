class Solution {
    public int[] sortArray(int[] nums) {
        return mergeSort(nums, 0, nums.length - 1);
    }
    
    private int[] mergeSort(int[] nums, int left, int right) {
        if (left == right) {
            return new int[]{nums[left]};
        }
        
        int mid = left + (right - left) / 2;
        int[] leftArr = mergeSort(nums, left, mid);
        int[] rightArr = mergeSort(nums, mid + 1, right);
        return merge(leftArr, rightArr);
    }
    
    private int[] merge(int[] left, int[] right) {
        int[] result = new int[left.length + right.length];
        int i = 0, j = 0, k = 0;
        
        while (i < left.length && j < right.length) {
            if (left[i] <= right[j]) {
                result[k++] = left[i++];
            } else {
                result[k++] = right[j++];
            }
        }
        
        while (i < left.length) {
            result[k++] = left[i++];
        }
        while (j < right.length) {
            result[k++] = right[j++];
        }
        
        return result;
    }
}
