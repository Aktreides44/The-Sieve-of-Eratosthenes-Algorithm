import sys
import time

def count_primes(N: int) -> int:
    # Initialize the flag for all numbers in grid to 1
    flags = bytearray([1]) * (N + 1)
    
    # Initialize 0 and 1 as flag 0 
    flags[0] = 0
    flags[1] = 0    
    
    # Mark all multiples to 0 up to limit of sqrt of N
    limit = int(N**0.5)
    for p in range(2, limit + 1):
        if flags[p] == 1:
            for k in range(p * p, N + 1, p):
                flags[k] = 0
                
    # Count flags equal to 1
    count = 0
    for flag in flags:
        if flag == 1:
            count += 1
            
    return count

def run_benchmark(N: int, warmup_runs: int = 5, measured_runs: int = 10):
    # warm-up calls
    for _ in range(warmup_runs):
        _ = count_primes(N)
        
    # timed calls
    timings_ms = []
    last_count = 0
    for _ in range(measured_runs):
        start = time.perf_counter()
        last_count = count_primes(N)
        end = time.perf_counter()
        timings_ms.append((end - start) * 1000.0)
        
    return timings_ms, last_count


if __name__ == "__main__":
    print("Task 2: Python Performance Measurement ")
    for N in [10**5, 10**6, 10**7]:
        timings, count = run_benchmark(N)
        print(f"N = 10^{len(str(N))-1} | pi(N) = {count}")
        print(f"  Runs (ms): {[round(t, 3) for t in timings]}")
        print(f"  Median: {round(sorted(timings)[len(timings)//2], 3)} ms\n")
