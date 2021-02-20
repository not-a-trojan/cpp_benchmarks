#pragma once

#include "types.h"
#include "utils.h"

#include <benchmark/benchmark.h>

void noop_benchmark(benchmark::State& state)
{
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(0);
    }
}

void prepare_benchmarks(); // implemented in respective source file

int main(int argc, char** argv)
{
    benchmark::RegisterBenchmark("__BaselineNoop__", noop_benchmark);
    prepare_benchmarks();
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
