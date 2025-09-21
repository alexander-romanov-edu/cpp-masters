#include <stwine/string_twine.hpp>

#include <benchmark/benchmark.h>

#include <array>
#include <random>
#include <string>
const char *str =
    "my very very very long string that doesn't fit into SSO buffer";

static std::string add_get() {
  return std::string(str) + str + str + str + str + str + str + str + str +
         str +
         (std::string(str) + str + str + str + str + str + str + str + str +
          str);
}

static std::string twine_get() {
  return (mcpp::string_twine(str) + str + str + str + str + str + str + str +
          str + str +
          (mcpp::string_twine(str) + str + str + str + str + str + str + str +
           str + str))
      .str();
}

static void add_bench(benchmark::State &state) {
  for (auto _ : state) {
    auto s = add_get();
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(add_bench);

static void twine_bench(benchmark::State &state) {
  for (auto _ : state) {
    auto s = twine_get();
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(twine_bench);

BENCHMARK_MAIN();
