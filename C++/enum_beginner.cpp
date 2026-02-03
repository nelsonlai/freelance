/*
 * ENUM BEGINNER EXAMPLES
 * 
 * This file demonstrates basic enum concepts in C++:
 * - Basic enum declaration and usage
 * - Enum values and their integer representations
 * - Switch statements with enums
 * - Enum comparisons and assignments
 * - Different ways to declare enums
 * 
 * Learning Objectives:
 * - Understand what an enum is and how to declare one
 * - Learn how enum values are assigned integer values
 * - Master using enums in switch statements
 * - Understand enum comparisons and assignments
 * - Learn different enum declaration styles
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
using namespace std; // Using standard namespace (for beginners)

/*
 * BASIC ENUM DECLARATION
 * 
 * An enum (enumeration) is a user-defined data type that consists of
 * a set of named integer constants. It makes code more readable and maintainable.
 * 
 * Key Points:
 * - Enum values are automatically assigned integer values starting from 0
 * - Each subsequent value is incremented by 1
 * - Enum values are constants and cannot be changed
 * - Enum names should be descriptive and follow naming conventions
 */
enum Color {
    RED,    // 0 (automatically assigned)
    GREEN,  // 1 (automatically assigned)
    BLUE,   // 2 (automatically assigned)
    YELLOW, // 3 (automatically assigned)
    PURPLE  // 4 (automatically assigned)
};

/*
 * ENUM WITH CUSTOM VALUES
 * 
 * You can explicitly assign integer values to enum members.
 * This is useful when you need specific values or want to skip numbers.
 * 
 * Key Points:
 * - You can assign any integer value to enum members
 * - Values don't have to be sequential
 * - You can assign the same value to multiple enum members
 * - Unassigned members continue from the last assigned value
 */
enum Day {
    MONDAY = 1,     // Explicitly set to 1
    TUESDAY = 2,    // Explicitly set to 2
    WEDNESDAY = 3,  // Explicitly set to 3
    THURSDAY = 4,   // Explicitly set to 4
    FRIDAY = 5,     // Explicitly set to 5
    SATURDAY = 6,   // Explicitly set to 6
    SUNDAY = 7      // Explicitly set to 7
};

/*
 * ENUM FOR GAME STATES
 * 
 * This enum represents different states in a game application.
 * Using enums for states makes the code more readable and less error-prone
 * than using magic numbers.
 * 
 * Key Points:
 * - Enums are perfect for representing a fixed set of states or options
 * - They make code self-documenting
 * - They prevent invalid values from being assigned
 * - They make switch statements more readable
 */
enum GameState {
    MENU,      // 0 - Game is showing the main menu
    PLAYING,   // 1 - Game is currently being played
    PAUSED,    // 2 - Game is paused
    GAME_OVER  // 3 - Game has ended
};

/*
 * HELPER FUNCTION: CONVERT ENUM TO STRING
 * 
 * This function converts a Color enum value to its string representation.
 * This is useful for displaying enum values in a human-readable format.
 * 
 * @param c The Color enum value to convert
 * @return A string representation of the color
 */
string colorToString(Color c) {
    switch (c) {
        case RED: return "Red";        // Return "Red" for RED enum value
        case GREEN: return "Green";    // Return "Green" for GREEN enum value
        case BLUE: return "Blue";      // Return "Blue" for BLUE enum value
        case YELLOW: return "Yellow";  // Return "Yellow" for YELLOW enum value
        case PURPLE: return "Purple";  // Return "Purple" for PURPLE enum value
        default: return "Unknown";     // Return "Unknown" for any other value
    }
}

/*
 * HELPER FUNCTION: CONVERT DAY ENUM TO STRING
 * 
 * This function converts a Day enum value to its string representation.
 * This demonstrates how to handle enums with custom values.
 * 
 * @param d The Day enum value to convert
 * @return A string representation of the day
 */
string dayToString(Day d) {
    switch (d) {
        case MONDAY: return "Monday";       // Return "Monday" for MONDAY enum value
        case TUESDAY: return "Tuesday";     // Return "Tuesday" for TUESDAY enum value
        case WEDNESDAY: return "Wednesday"; // Return "Wednesday" for WEDNESDAY enum value
        case THURSDAY: return "Thursday";   // Return "Thursday" for THURSDAY enum value
        case FRIDAY: return "Friday";       // Return "Friday" for FRIDAY enum value
        case SATURDAY: return "Saturday";   // Return "Saturday" for SATURDAY enum value
        case SUNDAY: return "Sunday";       // Return "Sunday" for SUNDAY enum value
        default: return "Unknown";          // Return "Unknown" for any other value
    }
}

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various ways to use enums in C++.
 * It shows enum declaration, assignment, comparison, and usage in
 * different contexts like switch statements, arrays, and function parameters.
 */
int main() {
    // Display program header
    cout << "=== ENUM BEGINNER EXAMPLES ===" << endl << endl;
    
    /*
     * EXAMPLE 1: BASIC ENUM USAGE
     * 
     * This demonstrates the most basic way to use an enum:
     * 1. Declare an enum variable
     * 2. Assign an enum value to it
     * 3. Use the enum value in expressions
     * 4. Convert enum to string for display
     */
    cout << "1. Basic Color Enum:" << endl;
    
    // Declare a Color enum variable and assign BLUE to it
    Color favoriteColor = BLUE;
    
    // Display the color name using our helper function
    cout << "My favorite color is: " << colorToString(favoriteColor) << endl;
    
    // Display the underlying integer value of the enum
    // BLUE has the value 2 (as defined in the enum)
    cout << "Color value: " << favoriteColor << endl;
    cout << endl;
    
    /*
     * EXAMPLE 2: ENUM WITH CUSTOM VALUES
     * 
     * This demonstrates how to use enums with explicitly assigned values.
     * The Day enum has values starting from 1 instead of 0.
     */
    cout << "2. Day Enum with Custom Values:" << endl;
    
    // Declare a Day enum variable and assign WEDNESDAY to it
    Day today = WEDNESDAY;
    
    // Display the day name using our helper function
    cout << "Today is: " << dayToString(today) << endl;
    
    // Display the underlying integer value (WEDNESDAY = 3)
    cout << "Day value: " << today << endl;
    cout << endl;
    
    /*
     * EXAMPLE 3: SWITCH STATEMENT WITH ENUM
     * 
     * This demonstrates how to use enums in switch statements.
     * Switch statements with enums are very common and make code
     * more readable than using magic numbers.
     */
    cout << "3. Switch Statement with Enum:" << endl;
    
    // Set the current game state to PLAYING
    GameState currentState = PLAYING;
    
    // Use switch statement to handle different game states
    switch (currentState) {
        case MENU:      // If state is MENU (0)
            cout << "Showing main menu..." << endl;
            break;      // Exit the switch statement
        case PLAYING:   // If state is PLAYING (1)
            cout << "Game is running..." << endl;
            break;      // Exit the switch statement
        case PAUSED:    // If state is PAUSED (2)
            cout << "Game is paused..." << endl;
            break;      // Exit the switch statement
        case GAME_OVER: // If state is GAME_OVER (3)
            cout << "Game over!" << endl;
            break;      // Exit the switch statement
    }
    cout << endl;
    
    /*
     * EXAMPLE 4: ENUM COMPARISON
     * 
     * This demonstrates how to compare enum values.
     * Enums can be compared using standard comparison operators
     * (==, !=, <, >, <=, >=).
     */
    cout << "4. Enum Comparison:" << endl;
    
    // Create two Color enum variables
    Color color1 = RED;   // color1 is RED (value 0)
    Color color2 = GREEN; // color2 is GREEN (value 1)
    
    // Compare color1 with RED (they are equal)
    if (color1 == RED) {
        cout << "Color1 is red!" << endl;
    }
    
    // Compare color1 with color2 (they are different)
    if (color1 != color2) {
        cout << "Color1 and Color2 are different!" << endl;
    }
    cout << endl;
    
    /*
     * EXAMPLE 5: ENUM IN ARRAY
     * 
     * This demonstrates how to use enums in arrays.
     * Arrays of enums are useful for storing multiple enum values
     * and iterating through them.
     */
    cout << "5. Enum in Array:" << endl;
    
    // Create an array of Color enums representing rainbow colors
    Color rainbow[] = {RED, YELLOW, GREEN, BLUE, PURPLE};
    
    cout << "Rainbow colors:" << endl;
    
    // Loop through the array and display each color
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << colorToString(rainbow[i]) << endl;
    }
    cout << endl;
    
    /*
     * EXAMPLE 6: ENUM AS FUNCTION PARAMETER
     * 
     * This demonstrates how to pass enums as function parameters.
     * We'll use a lambda function (anonymous function) to show
     * how enums can be passed to functions.
     */
    cout << "6. Enum as Function Parameter:" << endl;
    
    // Create a lambda function that takes a Day enum as parameter
    // The function displays both the string representation and the integer value
    auto printDayInfo = [](Day d) {
        cout << "Day: " << dayToString(d) << " (Value: " << d << ")" << endl;
    };
    
    // Call the lambda function with different Day enum values
    printDayInfo(MONDAY);   // Display Monday information
    printDayInfo(FRIDAY);   // Display Friday information
    printDayInfo(SUNDAY);   // Display Sunday information
    
    // Return 0 to indicate successful program execution
    return 0;
}
