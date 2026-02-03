#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {

    string line;

    // read input line by line until EOF
    while (getline(cin, line)) {

        int length = line.length();

        // reverse the line manually
        for (int i = 0; i < length / 2; i++ ) {
            char left = line[i];
            char right = line[length - i - 1];
            // left - convert to opposite case
            if (islower(left)) {
                left = toupper(left);
            } else if (isupper(left)) {
                left = tolower(left);
            }
            // right - convert to opposite case
            if (islower(right)) {
                right = toupper(right);
            } else if (isupper(right)) {
                right = tolower(right);
            }

            line[i] = right;
            line[length - i - 1] = left;
        }

        // print the reversed line
        cout << line << endl;
    }

    return 0;
}