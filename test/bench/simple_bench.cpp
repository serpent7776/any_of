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

/* 3 small strings test */

static void anyof_3strings_small(benchmark::State& state) {
	const std::string s = std::to_string(state.range(0));
	for (auto _ : state) {
		const bool r = s == srp::any_of(std::string("1"), std::string("2"), std::string("3"));
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(anyof_3strings_small)->Arg(0);

static void plain_3strings_small(benchmark::State& state) {
	const std::string s = std::to_string(state.range(0));
	for (auto _ : state) {
		const bool r = s == std::string("1") ||
			s == std::string("2") ||
			s == std::string("3");
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(plain_3strings_small)->Arg(0);

/* 3 big strings test */

static void anyof_3strings_big(benchmark::State& state) {
	const std::string s = std::to_string(state.range(0));
	for (auto _ : state) {
		const bool r = s == srp::any_of(
			std::string("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"),
			std::string("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"),
			std::string("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"));
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(anyof_3strings_big)->Arg(0);

static void plain_3strings_big(benchmark::State& state) {
	const std::string s = std::to_string(state.range(0));
	for (auto _ : state) {
		const bool r = s == std::string("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx") ||
			s == std::string("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy") ||
			s == std::string("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(plain_3strings_big)->Arg(0);

/* find_if test */

static void anyof_find_if(benchmark::State& state) {
	const auto vec = std::vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (auto _ : state) {
		const bool r = std::find(std::begin(vec), std::end(vec), srp::any_of(7, 8)) != std::end(vec);
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(anyof_find_if)->Arg(0);

static void plain_find_if(benchmark::State& state) {
	const auto vec = std::vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (auto _ : state) {
		const bool r = std::find_if(std::begin(vec), std::end(vec), [](int v)
		{
			return v == 7 || v == 8;
		}) != std::end(vec);
		benchmark::DoNotOptimize(r);
	}
}
BENCHMARK(plain_find_if)->Arg(0);

/* main */

BENCHMARK_MAIN();
