#include <benchmark/benchmark.h>

static void BM_SomeFunction(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        // SomeFunction();
    }
}

BENCHMARK(BM_SomeFunction);
