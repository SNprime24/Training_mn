#ifndef MERGE_SORT_H
#define MERGE_SORT_H

// Merges two sorted halves arr[left..mid] and arr[mid+1..right] into one sorted range.
void merge(int arr[], int left, int mid, int right);

// Sorts arr[left..right] in ascending order using merge sort. O(n log n) time.
void merge_sort(int arr[], int left, int right);

#endif
