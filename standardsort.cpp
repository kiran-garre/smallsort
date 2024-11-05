#include <stdio.h>
#include <vector>
#include <iterator>
#include <iostream>

extern "C" {
    void standard_sort_to_buffer(int* arr, int* stds, int length, int* buf);
}

/**
 * @param arr       Array to be sorted
 * @param stds      Rounded z-scores adjusted to [0,4]
 * @param length    Length of arr
 * @param buf       Buffer to be written to
 */
void standard_sort_to_buffer(int* arr, int* stds, int length, int* buf) {
    const int DIVISIONS = 41;
    const int ROW_SIZE = length / (DIVISIONS - 1);
    std::vector<int> sorted[DIVISIONS];
    for (int i = 0; i < DIVISIONS; i++) {
        sorted[i].reserve(ROW_SIZE);
    }

    for (int i = 0; i < length; i++) {
        int key = stds[i] % DIVISIONS;
        sorted[key].push_back(arr[i]);
    }

    int idx = 0;
    for (int i = 0; i < DIVISIONS; i++) {
        std::copy(sorted[i].begin(), sorted[i].end(), buf + idx);
        idx += sorted[i].size();
    }
}

