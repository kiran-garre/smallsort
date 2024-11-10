# SmallSort

This is a sorting algorithm that combines Counting Sort and IntroSort.

### How it works
Let's start with a random initial array: `[8.5, 4.2, 8.3, 4.0, 52.7, 9.4, 17.3, 53]`  
1. The first step is to find the rounded z-scores of each element, where the z-score is defined as `(x - mean) / std`:   
 `[-1, -1, -1, -1, 2, -1, 0, 2]`  
(In practice, we would round to 1 or 2 decimal places for smaller buckets.)  
2. Group elements into buckets based on their rounded z-scores:  
`[ -1,  -1,  -1,  -1,  -1,    0,  2,    2]`    
`[8.5, 4.2, 8.3, 4.0, 9.4, 17.3, 52.7, 53]`

3. In each bucket, run counting sort. If the numbers are floats, use their truncated values and keep track of the true float values in the output array:  
`[  4,   4,   8,   8,   9,   17,   52, 53]`  
`[4.2, 4.0, 8.5, 8.3, 9.4, 17.3, 52.7, 53]`

4. The previous steps ensure that the integer values within the array are all in the right order, so all we need to do is run `std::sort` (IntroSort) on each integer-value-separated
bucket of floats to sort the decimal part:  
`[4.0, 4.2, 8.3, 8.5, 9.4, 17.3, 52.7, 53]`

### Use cases
The sorting algoritm works best on arrays with a small range of values (~ -2<sup>24</sup> to 2<sup>24</sup>). This is because the runtime and space complexity of 
counting sort is heavily dependent on the range of values in the array. Grouping values by standard deviation helps to decrease the range each time counting sort is used,
but it still rapidly slows down for large ranges.

### To run
Simply use the provided makefile to generate the executables and import `small_sort` from `wrapper.py`. To see a quick time comparison between SmallSort and NumPy, run the `benchmark.py` file.
