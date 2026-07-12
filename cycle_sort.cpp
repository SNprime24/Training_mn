#include <bits/stdc++.h>
using namespace std;

void cycle_sort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i <= n-2; i++) {
        int item = arr[i];
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < item) pos++;
        }
        if (pos == i) continue;
        while (item == arr[pos]) pos++;

        swap(item, arr[pos]);

        while (pos != i) {
            pos = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < item) pos++;
            }
            while (item == arr[pos]) pos++;
            swap(item, arr[pos]);
        }
    }
}

int main() {
    vector<int> arr = {20, 40, 50, 10, 30};
    cycle_sort(arr);
    for (int x : arr) cout << x << " ";
}