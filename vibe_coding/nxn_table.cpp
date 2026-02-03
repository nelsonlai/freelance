#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printNxNTable(int n) {
    // Calculate the width needed for formatting
    int maxValue = n * n;
    int width = to_string(maxValue).length() + 1;
    
    // Print header row
    cout << setw(width) << " ";
    for (int i = 1; i <= n; i++) {
        cout << setw(width) << i;
    }
    cout << endl;
    
    // Print separator line
    cout << setw(width) << " ";
    for (int i = 1; i <= n; i++) {
        cout << string(width, '-');
    }
    cout << endl;
    
    // Print table rows
    for (int i = 1; i <= n; i++) {
        // Print row header
        cout << setw(width) << i << "|";
        
        // Print table values
        for (int j = 1; j <= n; j++) {
            cout << setw(width) << (i * j);
        }
        cout << endl;
    }
}

int main() {
    int n;
    
    cout << "Enter the size of the NxN table: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Error: N must be a positive integer." << endl;
        return 1;
    }
    
    cout << "\n" << n << "x" << n << " Multiplication Table:\n" << endl;
    printNxNTable(n);
    
    return 0;
}

