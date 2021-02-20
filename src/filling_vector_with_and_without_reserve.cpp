/*
This benchmark explores the differences in filling a std::vector, one element at a time, with and without using reserve().
*/

#include "benchmark.h"

void prepare_benchmarks()
{
    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        {
            std::string title = "pushing " + size_to_string(size) + " values into a std::vector<u64>; without reserve";
            benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
                for (auto _ : state)
                {
                    std::vector<u64> vec;
                    for (u64 i = 0; i < size; ++i)
                    {
                        vec.push_back(rng());
                    }
                    benchmark::DoNotOptimize(vec);
                }
            });
        }
        {
            std::string title = "pushing " + size_to_string(size) + " values into a std::vector<u64>; with reserve";
            benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
                for (auto _ : state)
                {
                    std::vector<u64> vec;
                    vec.reserve(size);
                    for (u64 i = 0; i < size; ++i)
                    {
                        vec.push_back(rng());
                    }
                    benchmark::DoNotOptimize(vec);
                }
            });
        }
    }
}
