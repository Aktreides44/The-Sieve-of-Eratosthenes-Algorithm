import matplotlib.pyplot as plt
import numpy as np

# Data collected from Task 2 runs
N_values = [10**5, 10**6, 10**7]

# Median times in milliseconds
cpp_medians = [0.101, 1.238, 25.866]
julia_medians = [0.174, 1.503, 25.800]
python_medians = [4.224, 40.858, 437.979]

# Create plot
plt.figure(figsize=(10, 6))

plt.plot(N_values, cpp_medians, marker='o', linewidth=2, label='C++ (g++ -O3)')
plt.plot(N_values, julia_medians, marker='s', linewidth=2, label='Julia (1.13)')
plt.plot(N_values, python_medians, marker='^', linewidth=2, label='Python (3.14)')

plt.xscale('log')
plt.yscale('log')

plt.title('Sieve of Eratosthenes Benchmark Performance', fontsize=14, fontweight='bold')
plt.xlabel('N (Array Size)', fontsize=12)
plt.ylabel('Median Execution Time (ms) - Log Scale', fontsize=12)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(fontsize=12)

# Save figure for lab submission
plt.tight_layout()
plt.savefig('sieve_performance.png', dpi=300)
print("Plot successfully saved as 'sieve_performance.png'")
