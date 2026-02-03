/**
 * Problem: Generate Random Point in a Circle
 * Difficulty: Medium
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private double radius;
    private double xCenter;
    private double yCenter;
    private Random random;

    public Solution(double radius, double x_center, double y_center) {
        this.radius = radius;
        this.xCenter = x_center;
        this.yCenter = y_center;
        this.random = new Random();
    }
    
    public double[] randPoint() {
        double angle = random.nextDouble() * 2 * Math.PI;
        double r = radius * Math.sqrt(random.nextDouble());
        double x = xCenter + r * Math.cos(angle);
        double y = yCenter + r * Math.sin(angle);
        return new double[]{x, y};
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(radius, x_center, y_center);
 * double[] param_1 = obj.randPoint();
 */