
#include <array>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <random>

template <class T>
void do_not_optimize_away(T&& datum) {
    asm volatile("" : "+r" (datum));
}

using val_type = int32_t;
constexpr std::size_t vals_per_gigabyte = ((1<<30) / sizeof(val_type));

static void array_sum(void) {
    constexpr int cardinality = 100;
    constexpr auto N = 4 * vals_per_gigabyte;

    int32_t *A = new int32_t[N];
    int64_t counts[cardinality]{};

    std::default_random_engine generator;
    std::uniform_int_distribution<int32_t> distribution(0, cardinality - 1);

    for (std::size_t i =0 ; i < N; ++i)
        A[i] = distribution(generator);

    auto start = std::chrono::system_clock::now();

    for (std::size_t i = 0; i < N; ++i)
        counts[A[i]]++;

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    int64_t sum{};
    for (auto i = 0; i < cardinality; ++i)
        sum += counts[i];
    do_not_optimize_away(sum);

    delete []A;
}

int main() {
  array_sum();
  return 0;
}
