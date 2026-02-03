#include <iostream>
#include <climits>
using namespace std;

double findMedianSortedArrays(int nums1[], int m, int nums2[], int n) {
    // Ensure nums1 is the smaller array
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }

    int left = 0, right = m;
    while (left <= right) {
        int i = (left + right) / 2;
        int j = (m + n + 1) / 2 - i;

        int maxLeftA  = (i == 0) ? INT_MIN : nums1[i - 1];
        int minRightA = (i == m) ? INT_MAX : nums1[i];
        int maxLeftB  = (j == 0) ? INT_MIN : nums2[j - 1];
        int minRightB = (j == n) ? INT_MAX : nums2[j];

        if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
            if ((m + n) % 2 == 0) {
                return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
            } else {
                return max(maxLeftA, maxLeftB);
            }
        } else if (maxLeftA > minRightB) {
            right = i - 1;
        } else {
            left = i + 1;
        }
    }

    return -1.0; // Should never happen for valid input
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    int m = sizeof(nums1) / sizeof(nums1[0]);
    int n = sizeof(nums2) / sizeof(nums2[0]);

    cout << "Median: " << findMedianSortedArrays(nums1, m, nums2, n) << endl;

    int nums3[] = {1, 2};
    int nums4[] = {3, 4};
    m = sizeof(nums3) / sizeof(nums3[0]);
    n = sizeof(nums4) / sizeof(nums4[0]);

    cout << "Median: " << findMedianSortedArrays(nums3, m, nums4, n) << endl;

    return 0;
}