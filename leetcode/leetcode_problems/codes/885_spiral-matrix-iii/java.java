import java.util.*;

class Solution {
    public int[][] spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        List<int[]> result = new ArrayList<>();
        int r = rStart, c = cStart;
        int dr = 0, dc = 1;
        int step = 1;
        
        while (result.size() < rows * cols) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < step; j++) {
                    if (r >= 0 && r < rows && c >= 0 && c < cols) {
                        result.add(new int[]{r, c});
                    }
                    r += dr;
                    c += dc;
                }
                int temp = dr;
                dr = dc;
                dc = -temp;
            }
            step++;
        }
        
        return result.toArray(new int[result.size()][]);
    }
}
