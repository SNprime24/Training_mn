#include "bubble_sort.h"

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        // size - i - 1 avoids comparing arr[j] with arr[j + 1] past the last element.
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
