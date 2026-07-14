# Training Media Net

C++ implementations of classic sorting algorithms for learning and practice.

## Algorithms

| Files | Algorithm | Time Complexity | Interface |
|-------|-----------|-----------------|-----------|
| `bubble_sort.h` / `bubble_sort.cpp` | Bubble Sort | O(n²) | `void bubble_sort(int arr[], int size)` |
| `selection_sort.h` / `selection_sort.cpp` | Selection Sort | O(n²) | `void selection_sort(int arr[], int size)` |
| `insertion_sort.h` / `insertion_sort.cpp` | Insertion Sort | O(n²) | `void insertion_sort(int arr[], int size)` |
| `merge_sort.h` / `merge_sort.cpp` | Merge Sort | O(n log n) | `void merge_sort(int arr[], int left, int right)` |
| `cycle_sort.h` / `cycle_sort.cpp` | Cycle Sort | O(n²) | `void cycle_sort(std::vector<int> &arr)` |
| `heap_sort.h` / `heap_sort.cpp` | Heap Sort | O(n log n) | `void heap_sort(int arr[], int size)` |

Each algorithm is split into a header (`.h`) for the public interface and an implementation file (`.cpp`).

## Usage

Include the header in your code and link the corresponding `.cpp` file, or include the implementation directly for a single-file build.

**Array-based sorts** (`bubble_sort`, `selection_sort`, `insertion_sort`, `heap_sort`):

```cpp
#include "bubble_sort.h"

int data[] = {5, 2, 8, 1, 9};
bubble_sort(data, 5);
```

**Merge sort** (divide-and-conquer on a range):

```cpp
#include "merge_sort.h"

int data[] = {5, 2, 8, 1, 9};
merge_sort(data, 0, 4);
```

**Heap sort** (in-place, array-based):

```cpp
#include "heap_sort.h"

int data[] = {5, 2, 8, 1, 9};
heap_sort(data, 5);
```

**Cycle sort** (operates on a `std::vector`):

```cpp
#include "cycle_sort.h"

std::vector<int> data = {5, 2, 8, 1, 9};
cycle_sort(data);
```

## Test Suite

`sorting_test.cpp` validates all algorithms against shared test cases (empty, single element, sorted, reverse sorted, duplicates, negatives, random, and large arrays).

Compile and run:

```bash
g++ -std=c++17 sorting_test.cpp -o build/sorting_test.exe
build/sorting_test.exe
```

The program prints `[PASS]` / `[FAIL]` for each case and exits with code `0` when all tests pass, or `1` if any fail.

Rebuild after changing source files — running a stale executable can produce incorrect results or crashes.
