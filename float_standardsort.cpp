#include <stdio.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>
#include <array>

extern "C" {
    void float_standard_sort_to_buffer(float* arr, int* stds, int length, float* buf);
}

std::vector<std::vector<float> > relative_counting_sort(std::vector<int> &, int, std::vector<float> &);

/**
 * @param arr       Array to be sorted
 * @param stds      Rounded z-scores adjusted to [0,4]
 * @param length    Length of arr
 * @param buf       Buffer to be written to
 */
void float_standard_sort_to_buffer(float* arr, int* stds, int length, float* buf) {
    const int DIVISIONS = 41;
    const int ROW_SIZE = length / (DIVISIONS - 1);
    std::vector<float> sorted[DIVISIONS];
    for (int i = 0; i < DIVISIONS; i++) {
        sorted[i].reserve(ROW_SIZE);
    }
    // std::cout << "Working until here" << std::endl;
    for (int i = 0; i < length; i++) {
        int key = std::max(0, std::min(stds[i], DIVISIONS - 1));
        sorted[key].push_back(arr[i]);
    }
    int idx = 0;
    for (int i = 0; i < DIVISIONS; i++) {
        if (!sorted[i].size()) {
            continue;
        }
        // std::sort(sorted[i].begin(), sorted[i].end());
        // radix_sort(sorted[i], sorted[i].size());
        // counting_sort(sorted[i], sorted[i].size());
        // dict_counting_sort(sorted[i], sorted[i].size());
        std::vector<int> truncated(sorted[i].begin(), sorted[i].end()); 
        std::vector<std::vector<float> > temp = relative_counting_sort(truncated, sorted[i].size(), sorted[i]);
        for (int j = 0; j < temp.size(); j++) {
            if (!temp.size()) 
                continue;
            std::sort(temp[j].begin(), temp[j].end());
            std::copy(temp[j].begin(), temp[j].end(), buf + idx);
            idx += temp[j].size();
        }   
    }
}

std::vector<std::vector<float> > relative_counting_sort(std::vector<int> & int_arr, int length, std::vector<float> & real_vals) {
    int max_val = *std::max_element(int_arr.begin(), int_arr.end());
    int min_val = *std::min_element(int_arr.begin(), int_arr.end());
    std::vector<std::vector<float> > output(max_val - min_val + 1);
    for (int i = 0; i < output.size(); i++) {
        output[i].reserve(10);
    }
    for (int i = 0; i < length; i++) {
        output[int_arr[i] - min_val].push_back(real_vals[i]);
    }
    return output;
}


