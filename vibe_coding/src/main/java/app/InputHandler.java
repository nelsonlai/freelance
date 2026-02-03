package app;

import java.util.Scanner;

/**
 * Handles user input and validation for the app.
 */
public class InputHandler {

    private static final String PROMPT = "Enter the size of the NxN table: ";

    public int readTableSize() {
        Scanner scanner = new Scanner(System.in);
        System.out.print(PROMPT);

        try {
            int n = scanner.nextInt();
            if (n <= 0) {
                System.err.println("Error: N must be a positive integer.");
                return -1;
            }
            return n;
        } catch (java.util.InputMismatchException e) {
            System.err.println("Error: Please enter a valid integer.");
            return -1;
        }
    }
}
