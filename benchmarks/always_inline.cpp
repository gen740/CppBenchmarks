#include <benchmark/benchmark.h>

#include <functional>
#include <iostream>

template <int N, class T>
__attribute__((noinline)) void NoInline(T&& fun) {
  if constexpr (N != 0) {
    fun();
    NoInline<N - 1>(fun);
  }
}

template <int N, class T>
__attribute__((always_inline)) void AlwaysInline(T&& fun) {
  if constexpr (N != 0) {
    fun();
    AlwaysInline<N - 1>(fun);
  }
}

volatile int a = 0;
constexpr int ITERS = 100;

static void NotAlwaysInlineBench(benchmark::State& state) {
  for (auto _ : state) {
    a = 0;
    NoInline<ITERS>([]() __attribute__((noinline)) { a += 1; });
  }
}

static void AlwaysInlineBench(benchmark::State& state) {
  for (auto _ : state) {
    a = 0;
    AlwaysInline<ITERS>([]() __attribute__((always_inline)) { a += 1; });
  }
}

static void JustFor(benchmark::State& state) {
  for (auto _ : state) {
    a = 0;
    for (int i = 0; i < ITERS; i++) {
      a += 1;
    }
  }
}

BENCHMARK(NotAlwaysInlineBench);
BENCHMARK(AlwaysInlineBench);
BENCHMARK(JustFor);
