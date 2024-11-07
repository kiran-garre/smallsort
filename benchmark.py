import timeit
import numpy as np
from wrapper import small_sort

if __name__ == '__main__':
    LOW = -1_000_000
    HIGH = 1_000_000

    LENGTH = 10_000_000
    LOOPS = 5

    int_rand_arr = np.random.randint(LOW, HIGH, (LENGTH,), dtype=np.int32)
    print(f'\nAveraging over {LOOPS} loops for {LENGTH:,} elements:')
    print()
    print('Integer arrays:')
    print(f'NumPy sort: {(timeit.timeit("np.sort(int_rand_arr)", globals=locals(), number=LOOPS) / LOOPS):.3f} seconds')
    print(f'SmallSort: {(timeit.timeit("small_sort(int_rand_arr)", globals=locals(), number=LOOPS) / LOOPS):.3f} seconds')
    print()
    
    float_rand_arr = np.random.uniform(LOW, HIGH, (LENGTH,)).astype(np.float32)
    print('Float arrays:')
    print(f'NumPy sort: {(timeit.timeit("np.sort(float_rand_arr)", globals=locals(), number=LOOPS) / LOOPS):.3f} seconds')
    print(f'SmallSort: {(timeit.timeit("small_sort(float_rand_arr)", globals=locals(), number=LOOPS) / LOOPS):.3f} seconds')
    print()

    result = (small_sort(int_rand_arr) == np.sort(int_rand_arr)).all()
    print(f'Integer accuracy test (1 run): Resulting arrays are the same -- {result}')
    result = (small_sort(float_rand_arr) == np.sort(float_rand_arr)).all()
    print(f'Float accuracy test (1 run): Resulting arrays are the same -- {result}')
    print()

