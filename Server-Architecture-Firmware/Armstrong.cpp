#include <iostream>
#include <cmath>
using namespace std;

bool isArmstrong(int n) {
    int original = n;
    int sum = 0;
    int digits = to_string(n).length();

    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, digits);
        n /= 10;
    }

    return sum == original;
}

int main() {
    int num = 153;
    cout << num << " is Armstrong? " << boolalpha << isArmstrong(num) << endl;

    num = 9474;
    cout << num << " is Armstrong? " << boolalpha << isArmstrong(num) << endl;

    num = 123;
    cout << num << " is Armstrong? " << boolalpha << isArmstrong(num) << endl;

    return 0;
}