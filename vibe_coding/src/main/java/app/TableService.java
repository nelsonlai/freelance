package app;

/**
 * Core business logic: generates an NxN multiplication table.
 */
public class TableService {

    /**
     * Builds an NxN multiplication table.
     * table[i][j] = (i+1) * (j+1) for 0-based indices.
     */
    public int[][] generate(int n) {
        int[][] table = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                table[i][j] = (i + 1) * (j + 1);
            }
        }
        return table;
    }
}
