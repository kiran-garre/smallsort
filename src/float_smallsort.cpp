#include <stdio.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>
#include <array>

extern "C" {
    void float_small_sort_to_buffer(float* arr, int* stds, int length, float* buf);
}

std::vector<float> relative_counting_sort(std::vector<int> &, int, std::vector<float> &);

/**
 * @param arr       Array to be sorted
 * @param stds      Rounded z-scores adjusted to [0,4]
 * @param length    Length of arr
 * @param buf       Buffer to be written to
 */
void float_small_sort_to_buffer(float* arr, int* stds, int length, float* buf) {
    const int DIVISIONS = 41;
    const int ROW_SIZE = length / (DIVISIONS - 1);
    std::vector<float> sorted[DIVISIONS];
    for (int i = 0; i < DIVISIONS; ++i) {
        sorted[i].reserve(ROW_SIZE);
    }
    for (int i = 0; i < length; ++i) {
        int key = std::max(0, std::min(stds[i], DIVISIONS - 1));
        sorted[key].push_back(arr[i]);
    }
    int idx = 0;
    for (int i = 0; i < DIVISIONS; ++i) {
        if (!sorted[i].size()) 
            continue;
        std::vector<int> truncated(sorted[i].begin(), sorted[i].end()); 
        std::vector<float> temp = relative_counting_sort(truncated, sorted[i].size(), sorted[i]);
        int prev_val_idx = 0;
        for (int j = 1; j < temp.size(); ++j) {
            if ((int)temp[j] != (int)temp[prev_val_idx]) {
                std::sort(temp.begin() + prev_val_idx, temp.begin() + j);
                prev_val_idx = j;
            }
        }   
        std::sort(temp.begin() + prev_val_idx, temp.end());
        std::copy(temp.begin(), temp.end(), buf + idx);
        idx += temp.size();
    }
}

std::vector<float> relative_counting_sort(std::vector<int> & int_arr, int length, std::vector<float> & real_vals) {
    auto [min, max] = std::minmax_element(int_arr.begin(), int_arr.end());
    if (*min == *max) {
        return real_vals;
    }
    std::vector<float> output(length);
    std::vector<int> counts(*max - *min + 1);
    for (int i = 0; i < length; ++i) {
        counts[int_arr[i] - *min]++;
    }
    for (int i = 1; i < counts.size(); ++i) {
        counts[i] += counts[i - 1];
    }
    for (int i = 0; i < length; ++i) {
        output[(counts[int_arr[i] - *min]--) - 1] = real_vals[i];
    }
    return output;
}

