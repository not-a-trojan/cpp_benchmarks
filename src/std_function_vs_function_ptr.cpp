/*
This benchmark explores the call overhead of invoking a list of std::function compared to function pointers, both stored in a std::vector.
Content of the functions is similar.
A typical situation where this is interesting would be invoking (a collection of) callback functions.
*/

#include "benchmark.h"

#include <functional>

u64 add(u64 x, u64 y)
{
    return x + y;
}
u64 sub(u64 x, u64 y)
{
    return x - y;
}
u64 mul(u64 x, u64 y)
{
    return x * y;
}
u64 get1(u64 x, u64)
{
    return x;
}
u64 get2(u64, u64 y)
{
    return y;
}
u64 sq(u64 x, u64 y)
{
    return x * x + y * y;
}

using arith_std_func = std::function<u64(u64, u64)>;
using arith_func = u64 (*)(u64, u64);

void prepare_benchmarks()
{
    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        constexpr int choices = 6;
        std::array<arith_std_func, choices> std_funcs = {[](u64 a, u64 b) { return a + b; },
                                                         [](u64 a, u64 b) { return a - b; },
                                                         [](u64 a, u64 b) { return a * b; },
                                                         [](u64 a, u64) { return a; },
                                                         [](u64, u64 b) { return b; },
                                                         [](u64 a, u64 b) { return a * a + b * b; }};

        std::array<arith_func, choices> normal_funcs = {&add,
                                                        &sub,
                                                        &mul,
                                                        &get1,
                                                        &get2,
                                                        &sq};

        std::vector<arith_std_func> std_functions;
        std::vector<arith_func> functions;
        {
            for (u64 i = 0; i < size; ++i)
            {
                auto choice = rng() % choices;
                std_functions.push_back(std_funcs[choice]);
                functions.push_back(normal_funcs[choice]);
            }
        }

        {
            std::string title = size_to_string(size) + " function calls; via function pointer";
            benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
                rng.seed(0);
                for (auto _ : state)
                {
                    for (auto& f : functions)
                    {
                        auto x = f(rng(), rng());
                        benchmark::DoNotOptimize(x);
                    }
                }
            });
        }
        {
            std::string title = size_to_string(size) + " function calls; via std::function";
            benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
                rng.seed(0);
                for (auto _ : state)
                {
                    for (auto& f : std_functions)
                    {
                        auto x = f(rng(), rng());
                        benchmark::DoNotOptimize(x);
                    }
                }
            });
        }
    }
}
