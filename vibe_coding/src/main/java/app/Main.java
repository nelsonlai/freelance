package app;

/**
 * Entry point for the NxN table application.
 * Wires input, business logic, and output together.
 */
public class Main {

    public static void main(String[] args) {
        InputHandler input = new InputHandler();
        TableService tableService = new TableService();
        TablePrinter tablePrinter = new TablePrinter();

        int n = input.readTableSize();
        if (n <= 0) {
            return;
        }

        int[][] table = tableService.generate(n);
        tablePrinter.print(n, table);
    }
}
