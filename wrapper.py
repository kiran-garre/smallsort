import numpy as np
import ctypes
from numpy.ctypeslib import ndpointer

int_lib = ctypes.CDLL('./executables/int_smallsort.so')
int_lib.int_small_sort_to_buffer.argtypes = [
    ndpointer(np.int32, flags="C_CONTIGUOUS"), 
    ndpointer(np.int32, flags="C_CONTIGUOUS"), 
    ctypes.c_int,
    ndpointer(np.int32, flags="C_CONTIGUOUS"),
]

float_lib = ctypes.CDLL('./executables/float_smallsort.so')
float_lib.float_small_sort_to_buffer.argtypes = [
    ndpointer(np.float32, flags="C_CONTIGUOUS"), 
    ndpointer(np.int32, flags="C_CONTIGUOUS"), 
    ctypes.c_int,
    ndpointer(np.float32, flags="C_CONTIGUOUS"),
]

int_types = [np.int32]
float_types = [np.float32]

def small_sort(arr):
    DIVISONS = 41
    assert isinstance(arr, np.ndarray)
    dtype = arr.dtype
    
    avg = np.mean(arr)
    std = np.std(arr)
    ret_buf = np.empty_like(arr, dtype=dtype)
    adjusted_z_scores = (np.round((arr - avg) / std, decimals=1) * ((DIVISONS - 1) / 4) + (DIVISONS - 1) / 2).astype(np.int32)
    
    if dtype in int_types:
        int_lib.int_small_sort_to_buffer(arr, adjusted_z_scores, arr.size, ret_buf)
    elif dtype in float_types:
        float_lib.float_small_sort_to_buffer(arr, adjusted_z_scores, arr.size, ret_buf)
    else:
        raise Exception(f"Type {dtype} not supported")
    
    return ret_buf



