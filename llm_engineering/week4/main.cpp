#include <cstdio>
#include <cstdint>
#include <chrono>

#pragma STDC FENV_ACCESS ON

static inline double calculate(uint32_t iterations, int param1, int param2) {
    #pragma clang fp reassociate(off)
    #pragma clang fp contract(off)
    #pragma clang fp eval_method(source)

    const double p1 = static_cast<double>(param1);
    const double p2 = static_cast<double>(param2);

    double result = 1.0;

    #pragma clang loop vectorize(disable)
    #pragma clang loop interleave(disable)
    for (uint32_t i = 1; i <= iterations; ++i) {
        double base = static_cast<double>(i) * p1;
        result -= 1.0 / (base - p2);
        result += 1.0 / (base + p2);
    }
    return result;
}

int main() {
    using clock = std::chrono::steady_clock;
    auto start_time = clock::now();

    double result = calculate(200000000u, 4, 1) * 4.0;

    auto end_time = clock::now();
    double elapsed = std::chrono::duration<double>(end_time - start_time).count();

    std::printf("Result: %.12f\n", result);
    std::printf("Execution Time: %.6f seconds\n", elapsed);
    return 0;
}