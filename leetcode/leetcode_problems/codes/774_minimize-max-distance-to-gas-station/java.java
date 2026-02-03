class Solution {
    public double minmaxGasDist(int[] stations, int k) {
        double left = 0, right = stations[stations.length - 1] - stations[0];
        while (right - left > 1e-6) {
            double mid = (left + right) / 2.0;
            if (possible(stations, k, mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }
    
    private boolean possible(int[] stations, int k, double D) {
        int count = 0;
        for (int i = 0; i < stations.length - 1; i++) {
            count += (int)((stations[i + 1] - stations[i]) / D);
        }
        return count <= k;
    }
}
