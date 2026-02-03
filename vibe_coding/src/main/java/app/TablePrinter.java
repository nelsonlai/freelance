package app;

/**
 * Formats and prints an NxN table to the console.
 */
public class TablePrinter {

    public void print(int n, int[][] table) {
        int maxValue = n * n;
        int width = String.valueOf(maxValue).length() + 1;

        // Header row
        System.out.printf("%" + width + "s", " ");
        for (int j = 0; j < n; j++) {
            System.out.printf("%" + width + "d", j + 1);
        }
        System.out.println();

        // Separator
        System.out.printf("%" + width + "s", " ");
        for (int j = 0; j < n; j++) {
            System.out.print("-".repeat(width));
        }
        System.out.println();

        // Table rows
        for (int i = 0; i < n; i++) {
            System.out.printf("%" + width + "d|", i + 1);
            for (int j = 0; j < n; j++) {
                System.out.printf("%" + width + "d", table[i][j]);
            }
            System.out.println();
        }
    }
}
