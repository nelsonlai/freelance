/**
 * Problem: Erect the Fence II
 * Difficulty: Hard
 * Tags: array, math, geometry, smallest enclosing circle
 * 
 * Approach: Find smallest circle enclosing all points (Welzl's algorithm)
 * Time Complexity: O(n) expected
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public double[] outerTrees(int[][] trees) {
        if (trees.length == 1) {
            return new double[]{trees[0][0], trees[0][1], 0.0};
        }
        
        List<int[]> points = new ArrayList<>();
        for (int[] tree : trees) {
            points.add(new int[]{tree[0], tree[1]});
        }
        
        double[] circle = welzl(points, new ArrayList<>());
        return new double[]{
            Math.round(circle[0] * 100000.0) / 100000.0,
            Math.round(circle[1] * 100000.0) / 100000.0,
            Math.round(circle[2] * 100000.0) / 100000.0
        };
    }
    
    private double dist(int[] p1, int[] p2) {
        double dx = p1[0] - p2[0];
        double dy = p1[1] - p2[1];
        return Math.sqrt(dx * dx + dy * dy);
    }
    
    private double dist(double[] p1, int[] p2) {
        double dx = p1[0] - p2[0];
        double dy = p1[1] - p2[1];
        return Math.sqrt(dx * dx + dy * dy);
    }
    
    private double[] circleFrom2Points(int[] p1, int[] p2) {
        double cx = (p1[0] + p2[0]) / 2.0;
        double cy = (p1[1] + p2[1]) / 2.0;
        double r = dist(p1, p2) / 2.0;
        return new double[]{cx, cy, r};
    }
    
    private double[] circleFrom3Points(int[] p1, int[] p2, int[] p3) {
        double ax = p1[0], ay = p1[1];
        double bx = p2[0], by = p2[1];
        double cx = p3[0], cy = p3[1];
        
        double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
        if (Math.abs(d) < 1e-9) {
            return null;
        }
        
        double ux = ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + 
                     (cx*cx + cy*cy) * (ay - by)) / d;
        double uy = ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + 
                     (cx*cx + cy*cy) * (bx - ax)) / d;
        
        double r = dist(new double[]{ux, uy}, p1);
        return new double[]{ux, uy, r};
    }
    
    private boolean isInside(double[] circle, int[] p) {
        if (circle == null) return false;
        double cx = circle[0], cy = circle[1], r = circle[2];
        return dist(new double[]{cx, cy}, p) <= r + 1e-9;
    }
    
    private double[] welzl(List<int[]> points, List<int[]> R) {
        if (points.isEmpty() || R.size() == 3) {
            if (R.isEmpty()) {
                return null;
            } else if (R.size() == 1) {
                return new double[]{R.get(0)[0], R.get(0)[1], 0.0};
            } else if (R.size() == 2) {
                return circleFrom2Points(R.get(0), R.get(1));
            } else {
                return circleFrom3Points(R.get(0), R.get(1), R.get(2));
            }
        }
        
        int[] p = points.get(0);
        List<int[]> remaining = points.subList(1, points.size());
        double[] circle = welzl(new ArrayList<>(remaining), R);
        
        if (circle == null || !isInside(circle, p)) {
            List<int[]> newR = new ArrayList<>(R);
            newR.add(p);
            circle = welzl(new ArrayList<>(remaining), newR);
        }
        
        return circle;
    }
}