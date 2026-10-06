#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

// Function that returns the count of primes <= N
uint64_t count_primes(uint64_t N) {
    // 1. Allocate N + 1 flags initialized to 1 (using uint8_t for 1-byte representation)
    std::vector<uint8_t> flags(N + 1, 1);

    // 2. Set flags for 0 and 1 to 0
    flags[0] = 0;
    flags[1] = 0;

    // 3. Mark multiples of primes up to sqrt(N)
    uint64_t limit = static_cast<uint64_t>(std::sqrt(N));
    for (uint64_t p = 2; p <= limit; ++p) {
        if (flags[p] == 1) {
            for (uint64_t k = p * p; k <= N; k += p) {
                flags[k] = 0;
            }
        }
    }

    // 4. Count remaining flags equal to 1 using an explicit loop
    uint64_t count = 0;
    for (uint64_t i = 0; i <= N; ++i) {
        if (flags[i] == 1) {
            count++;
        }
    }

    return count;
}

int main() {
    uint64_t test_values[] = {2, 10, 100, 100000, 1000000, 10000000};

    std::cout << "--- Correctness Checks (C++) ---\n";
    for (uint64_t N : test_values) {
        std::cout << "N = " << N << "\t | pi(N) = " << count_primes(N) << "\n";
    }

    return 0;
}
