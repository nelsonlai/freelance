/**
 * Problem: Statistics from a Large Sample
 * Difficulty: Medium
 * Tags: array, math, sort
 * 
 * Approach: Calculate min, max, mean, median, mode from count array
 * Time Complexity: O(n) where n is count length
 * Space Complexity: O(1)
 */

class Solution {
    public double[] sampleStats(int[] count) {
        int total = 0;
        int minVal = -1, maxVal = -1;
        long sum = 0;
        int mode = 0;
        int maxCount = 0;
        
        for (int i = 0; i < count.length; i++) {
            if (count[i] > 0) {
                if (minVal == -1) minVal = i;
                maxVal = i;
                total += count[i];
                sum += (long) i * count[i];
                if (count[i] > maxCount) {
                    maxCount = count[i];
                    mode = i;
                }
            }
        }
        
        double mean = (double) sum / total;
        double median = 0;
        int cumsum = 0;
        for (int i = 0; i < count.length; i++) {
            cumsum += count[i];
            if (cumsum >= (total + 1) / 2) {
                if (total % 2 == 1) {
                    median = i;
                } else {
                    if (cumsum > total / 2) {
                        median = i;
                    } else {
                        for (int j = i + 1; j < count.length; j++) {
                            if (count[j] > 0) {
                                median = (i + j) / 2.0;
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
        
        return new double[]{minVal, maxVal, mean, median, mode};
    }
}