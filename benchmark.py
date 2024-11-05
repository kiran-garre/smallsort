import timeit
import numpy as np
from wrapper import standard_sort

if __name__ == '__main__':
    LENGTH = 1_000_000
    LOOPS = 10

    rand_arr = np.random.randint(0, 100000, (LENGTH,), dtype=np.int32)
    print(f'\nAveraging over {LOOPS} loops for {LENGTH} elements:')
    print(f'\nPython built-in: {(timeit.timeit("sorted(rand_arr)", globals=locals(), number=LOOPS) / LOOPS):.3f} seconds')
    print(f'Using z-score pre-sorting: {(timeit.timeit("sorted(standard_sort(rand_arr))", globals=locals(), number=LOOPS) / LOOPS):.3f} seconds\n')
