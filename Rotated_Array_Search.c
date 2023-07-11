#include <stdio.h>

int search_in_rotated_array(int nums[], int target, int n) {
    // Logic
    int start = 0;
    int end = n - 1;

    while (start <= end) {
        int mid = (start + end) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        // Two cases
        if (nums[start] <= nums[mid]) {
            // Left
            if (target >= nums[start] && target <= nums[mid]) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        } else {
            // Right
            if (target >= nums[mid] && target <= nums[end]) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
    }

    return -1;
}

int main() {
    int nums[] = {4, 5, 6, 7, 0, 1, 2, 3};
    int target = 0;
    int n = sizeof(nums) / sizeof(nums[0]);

    int result = search_in_rotated_array(nums, target, n);
    printf("%d\n", result);

    return 0;
}
