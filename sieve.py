import sys
import time

def count_primes(N: int) -> int:
    # 1. Initialize the flag for all numbers in grid to 1
    flags = bytearray([1]) * (N + 1)
    
    # 2. Initialize 0 and 1 as flag 0 
    flags[0] = 0
    flags[1] = 0    
    
    # 3. Mark all multiples to 0 up to limit of sqrt of N
    limit = int(N**0.5)
    for p in range(2, limit + 1):
        if flags[p] == 1:
            for k in range(p * p, N + 1, p):
                flags[k] = 0
                
    # 4. Count flags equal to 1
    count = 0
    for flag in flags:
        if flag == 1:
            count += 1
            
    return count

if __name__ == "__main__":
    # Quick correctness check on required test values
    test_values = [2, 10, 100, 10**5, 10**6, 10**7]
    print("--- Correctness Checks ---")
    for N in test_values:
        print(f"N = {N:<8} | pi(N) = {count_primes(N)}")
