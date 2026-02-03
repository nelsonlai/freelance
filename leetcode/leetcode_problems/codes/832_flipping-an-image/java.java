class Solution {
    public int[][] flipAndInvertImage(int[][] image) {
        int n = image.length;
        for (int i = 0; i < n; i++) {
            int left = 0, right = n - 1;
            while (left <= right) {
                int temp = 1 - image[i][left];
                image[i][left] = 1 - image[i][right];
                image[i][right] = temp;
                left++;
                right--;
            }
        }
        return image;
    }
}
