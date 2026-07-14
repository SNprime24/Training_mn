#include "merge_sort.h"

void merge(int arr[], int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Temporary buffers hold copies of the two sorted halves.
    int left_arr[left_size];
    int right_arr[right_size];

    for (int i = 0; i < left_size; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < right_size; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_size && j < right_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }

    // Copy any remaining elements from the half that was not exhausted.
    while (i < left_size) {
        arr[k++] = left_arr[i++];
    }
    while (j < right_size) {
        arr[k++] = right_arr[j++];
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
