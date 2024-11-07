#include <stdio.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>
#include <array>
#include <unordered_map>

extern "C" {
    void int_small_sort_to_buffer(int* arr, int* stds, int length, int* buf);
}

void counting_sort(std::vector<int> &, int);
int quick_pow10(int);

/**
 * @param arr       Array to be sorted
 * @param stds      Rounded z-scores adjusted to [0,4]
 * @param length    Length of arr
 * @param buf       Buffer to be written to
 */
void int_small_sort_to_buffer(int* arr, int* stds, int length, int* buf) {
    const int DIVISIONS = 41;
    const int ROW_SIZE = length / (DIVISIONS - 1);
    std::vector<int> sorted[DIVISIONS];
    for (int i = 0; i < DIVISIONS; i++) {
        sorted[i].reserve(ROW_SIZE);
    }

    for (int i = 0; i < length; i++) {
        int key = std::max(0, std::min(stds[i], DIVISIONS - 1));
        sorted[key].push_back(arr[i]);
    }

    int idx = 0;
    for (int i = 0; i < DIVISIONS; i++) {
        counting_sort(sorted[i], sorted[i].size());
        std::copy(sorted[i].begin(), sorted[i].end(), buf + idx);
        idx += sorted[i].size();
    }
}

int quick_pow10(int n) {
    static int pow10[10] = {
        1, 10, 100, 1000, 10000, 
        100000, 1000000, 10000000, 100000000, 1000000000
    };
    return pow10[n]; 
}

void counting_sort(std::vector<int> & arr, int length) {
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());
    std::vector<int> output(length);
    std::vector<int> counts(max_val - min_val + 1, 0); 
    
    for (int i = 0; i < length; i++) {
        counts[arr[i] - min_val]++;
    }
    for (int i = 1; i <= max_val - min_val; i++) {
        counts[i] += counts[i - 1];
    }
    for (int i = length - 1; i >= 0; i--) {
        output[(counts[arr[i] - min_val]--) - 1] = arr[i];
    }
    std::copy(output.begin(), output.end(), arr.begin());
}