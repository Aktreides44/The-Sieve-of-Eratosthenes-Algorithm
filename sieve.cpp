#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <iomanip>

// Function that returns the count of primes <= N
uint64_t count_primes(uint64_t N) {
    // Allocate N + 1 flags initialized to 1 (using uint8_t for 1-byte representation)
    std::vector<uint8_t> flags(N + 1, 1);

    // Set flags for 0 and 1 to 0
    flags[0] = 0;
    flags[1] = 0;

    // Mark multiples of primes up to sqrt(N)
    uint64_t limit = static_cast<uint64_t>(std::sqrt(N));
    for (uint64_t p = 2; p <= limit; ++p) {
        if (flags[p] == 1) {
            for (uint64_t k = p * p; k <= N; k += p) {
                flags[k] = 0;
            }
        }
    }

    // Count remaining flags equal to 1 using an explicit loop
    uint64_t count = 0;
    for (uint64_t i = 0; i <= N; ++i) {
        if (flags[i] == 1) {
            count++;
        }
    }

    return count;
}

void run_benchmark(uint64_t N, int warmup_runs = 5, int measured_runs = 10) {
    // Warm-up calls
    for (int i = 0; i < warmup_runs; ++i) {
        volatile uint64_t dummy = count_primes(N);
        (void)dummy;
    }

    // Timed calls
    std::vector<double> timings_ms;
    uint64_t last_count = 0;

    for (int i = 0; i < measured_runs; ++i) {
        auto start = std::chrono::steady_clock::now();
        last_count = count_primes(N);
        auto end = std::chrono::steady_clock::now();
        
        std::chrono::duration<double, std::milli> elapsed = end - start;
        timings_ms.push_back(elapsed.count());
    }

    std::cout << "N = " << N << " | pi(N) = " << last_count << "\n";
    std::cout << "  Runs (ms): ";
    for (double t : timings_ms) {
        std::cout << std::fixed << std::setprecision(3) << t << " ";
    }
    std::cout << "\n";

    std::vector<double> sorted_t = timings_ms;
    std::sort(sorted_t.begin(), sorted_t.end());
    std::cout << "  Median: " << sorted_t[sorted_t.size() / 2] << " ms\n\n";
}

int main() {
    std::cout << "--- Task 2: C++ Performance Measurement ---\n";
    run_benchmark(100000);
    run_benchmark(1000000);
    run_benchmark(10000000);
    return 0;
}

