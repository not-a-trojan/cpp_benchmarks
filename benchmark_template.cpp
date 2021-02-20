/*
This is an (optional but recommended) description of the benchmark.
The description has to be a multiline comment and it has to be at the very top of the file.
It gets copied to the result report to provide context for readers.
*/

#include "benchmark.h"

// this function is called in the benchmark main
// all you have to do is add your benchmark functions via `benchmark::RegisterBenchmark`
// make sure to take all local data into lambdas by value, as references to local objects are not valid anymore when the benchmarks are executed
void prepare_benchmarks()
{
    std::string group_title = "benchmark group title"; // e.g., "iterate 10000 integers"
    std::string variant = "specific variant"; // e.g., "using std::set"

    benchmark::RegisterBenchmark(
        (group_title + ";" + variant).c_str(),  // group title and variant have to be separated by ';'
        [=](benchmark::State& state) {          // actual Google-benchmark-function as lambda or free function
            for (auto _ : state)
            {
                // do your benchmark
            }
        }
    );
}
