#include "cycle_sort.h"

#include <utility>

void cycle_sort(std::vector<int> &arr) {
    const int size = static_cast<int>(arr.size());

    for (int i = 0; i <= size - 2; i++) {
        int item = arr[i];
        int pos = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < item) {
                pos++;
            }
        }

        if (pos == i) {
            continue;
        }

        while (item == arr[pos]) {
            pos++;
        }

        std::swap(item, arr[pos]);

        while (pos != i) {
            pos = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < item) {
                    pos++;
                }
            }
            while (item == arr[pos]) {
                pos++;
            }
            std::swap(item, arr[pos]);
        }
    }
}
