using Statistics

function count_primes(N::Int64)::Int64
    # 1. Allocate N + 1 flags initialized to 1 (using UInt8 for 1-byte representation)
    flags = fill(UInt8(1), N + 1)
    
    # 2. Set flags for 0 and 1 (indices 1 and 2 in Julia) to 0
    flags[1] = 0
    flags[2] = 0

    # 3. Mark multiples of primes up to sqrt(N)
    limit = floor(Int64, sqrt(N))
    for p in 2:limit
        if flags[p + 1] == 1
            for k in (p * p):p:N
                flags[k + 1] = 0
            end
        end
    end

    # 4. Count remaining flags equal to 1 using an explicit loop
    count::Int64 = 0
    for i in 1:(N + 1)
        if flags[i] == 1
            count += 1
        end
    end

    return count
end

function run_benchmark(N::Int64; warmup_runs=5, measured_runs=10)
    # 1. Warm-up calls (forces JIT compilation inside process before timing)
    for _ in 1:warmup_runs
        count_primes(N)
    end

    # 2. Timed calls using time_ns()
    timings_ms = Float64[]
    last_count = 0
    for _ in 1:measured_runs
        t0 = time_ns()
        last_count = count_primes(N)
        t1 = time_ns()
        push!(timings_ms, (t1 - t0) / 1e6)
    end

    println("N = $N | pi(N) = $last_count")
    println("  Runs (ms): ", round.(timings_ms, digits=3))
    println("  Median: ", round(median(timings_ms), digits=3), " ms\n")
end

function main()
    println("--- Task 2: Julia Performance Measurement ---")
    run_benchmark(10^5)
    run_benchmark(10^6)
    run_benchmark(10^7)
end

main()
