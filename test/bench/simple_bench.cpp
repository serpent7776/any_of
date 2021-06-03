#include <string>

#include <benchmark/benchmark.h>

#include <any_of.hpp>

/* 4 ints test */

static void anyof_4int(benchmark::State& state) {
	const int value = state.range(0);
	for (auto _ : state) {
		const bool r = value == srp::any_of(10, 11, 12, 13);
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(anyof_4int)->Arg(12);

static void plain_4int(benchmark::State& state) {
	const int value = state.range(0);
	for (auto _ : state) {
		const bool r = value == 10 ||
			value == 11 ||
			value == 12 ||
			value == 13;
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(plain_4int)->Arg(12);

/* 3 strings test */

static void anyof_3strings(benchmark::State& state) {
	const std::string s = std::to_string(state.range(0));
	for (auto _ : state) {
		const bool r = s == srp::any_of(std::string("1"), std::string("2"), std::string("3"));
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(anyof_3strings)->Arg(0);

static void plain_3strings(benchmark::State& state) {
	const std::string s = std::to_string(state.range(0));
	for (auto _ : state) {
		const bool r = s == std::string("1") ||
			s == std::string("2") ||
			s == std::string("3");
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(plain_3strings)->Arg(0);

/* main */

BENCHMARK_MAIN();
