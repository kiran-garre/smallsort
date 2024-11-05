import numpy as np
import ctypes
from numpy.ctypeslib import ndpointer

lib = ctypes.CDLL('./standardsort.so')
lib.standard_sort_to_buffer.argtypes = [
    ndpointer(np.int32, flags="C_CONTIGUOUS"), 
    ndpointer(np.int32, flags="C_CONTIGUOUS"), 
    ctypes.c_int,
    ndpointer(np.int32),
]

def standard_sort(arr):
    assert isinstance(arr, np.ndarray)
    avg = np.mean(arr)
    std = np.std(arr)
    temp_arr = (np.round((arr - avg) / std, decimals=1) * 10 + 20).astype(np.int32)

    ret_arr = np.empty_like(arr, dtype=arr.dtype)
    lib.standard_sort_to_buffer(arr, temp_arr, arr.size, ret_arr)
    return ret_arr