import fast_math
import time

def slow_sum(n):
    res = 0
    for i in range(n):
        res += (i * i)
    return res

N = 10**7

start = time.time()
slow_sum(N)
print(f"Pure Python: {time.time() - start:.4f}s")

start = time.time()
fast_math.fast_sum(N)
print(f"C Extension: {time.time() - start:.4f}s")
