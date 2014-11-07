
#include <array>
#include <cstdint>
#include <random>

#include <benchmark/benchmark.h>

template <class T>
void do_not_optimize_away(T&& datum) {
    asm volatile("" : "+r" (datum));
}

using val_type = int32_t;
constexpr std::size_t vals_per_gigabyte = ((1<<30) / sizeof(val_type));

static void array_sum(benchmark::State& state) {
    constexpr auto N = 2 * vals_per_gigabyte;
    int32_t *A = new int32_t[N];

    while (state.KeepRunning()) {
        int64_t sum = 0;
        for (std::size_t i = 0; i < N; ++i)
            sum += A[i];

        do_not_optimize_away(sum);
    }

    delete []A;
}

BENCHMARK(array_sum);

int main(int argc, const char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  return 0;
}