#include <benchmark/benchmark.h>
#include <any_of.hpp>

static void anyof_f(benchmark::State& state) {
	for (auto _ : state) {
		const bool r = state.range(0) == srp::any_of(10, 11, 12, 13);
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(anyof_f)->Arg(12);

static void plain_f(benchmark::State& state) {
	for (auto _ : state) {
		const bool r = state.range(0) == 10 ||
			state.range(0) == 11 ||
			state.range(0) == 12 ||
			state.range(0) == 13;
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(plain_f)->Arg(12);

BENCHMARK_MAIN();
