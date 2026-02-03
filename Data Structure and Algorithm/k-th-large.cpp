#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Find the k-th largest by repeatedly selecting the max
int findKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    vector<bool> used(n, false);  // To mark used elements

    int maxVal;
    int maxIndex;

    for (int round = 0; round < k; ++round) {
        maxVal = INT_MIN;
        maxIndex = -1;

        // Find the current maximum unused element
        for (int i = 0; i < n; ++i) {
            if (!used[i] && nums[i] > maxVal) {
                maxVal = nums[i];
                maxIndex = i;
            }
        }

        // Mark this element as used
        used[maxIndex] = true;
    }

    return maxVal;  // k-th largest
}

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;

    int result = findKthLargest(nums, k);
    cout << "The " << k << "-th largest element is: " << result << endl;

    return 0;
}

// Quick Select Algorithm?!!