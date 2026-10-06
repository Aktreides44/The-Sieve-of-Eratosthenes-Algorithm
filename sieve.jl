function count_primes(N::Int64)::Int64
    # 1. Allocate N + 1 flags initialized to 1 (using UInt8 for 1-byte representation)
    # Position (n + 1) represents integer n.
    flags = fill(UInt8(1), N + 1)

    # 2. Set flags for 0 and 1 (indices 1 and 2 in Julia) to 0
    flags[1] = 0  # Represents number 0
    flags[2] = 0  # Represents number 1

    # 3. Mark multiples of primes up to sqrt(N)
    limit = floor(Int64, sqrt(N))
    for p in 2:limit
        if flags[p + 1] == 1
            # k runs from p*p to N with step p
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

function main()
    test_values = [2, 10, 100, 10^5, 10^6, 10^7]
    println("--- Correctness Checks (Julia) ---")
    for N in test_values
        println("N = ", rpad(N, 10), " | pi(N) = ", count_primes(N))
    end
end

main()
