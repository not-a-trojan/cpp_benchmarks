/*
This benchmark explores the differences in iterating over various STL containers via reference and iterators.
*/

#include "benchmark.h"

void prepare_benchmarks()
{
    auto register_benchmark_auto = [=](auto& collection) {
        std::string title = "iterating over " + size_to_string(collection.size()) + " elements; " + TypeName(collection) + ", using `auto&`";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
            for (auto _ : state)
            {
                if constexpr (is_map<decltype(collection)>)
                {
                    for (auto& [x, y] : collection)
                    {
                        benchmark::DoNotOptimize(x);
                        benchmark::DoNotOptimize(y);
                    }
                }
                else
                {
                    for (auto& x : collection)
                    {
                        benchmark::DoNotOptimize(x);
                    }
                }
            }
        });
    };

    auto register_benchmark_iterator = [=](auto& collection) {
        std::string title = "iterating over " + size_to_string(collection.size()) + " elements; " + TypeName(collection) + ", using iterator";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
            for (auto _ : state)
            {
                if constexpr (is_map<decltype(collection)>)
                {
                    for (auto it = collection.begin(); it != collection.end(); ++it)
                    {
                        auto& x = it->first;
                        auto& y = it->second;
                        benchmark::DoNotOptimize(x);
                        benchmark::DoNotOptimize(y);
                    }
                }
                else
                {
                    for (auto it = collection.begin(); it != collection.end(); ++it)
                    {
                        auto& x = *it;
                        benchmark::DoNotOptimize(x);
                    }
                }
            }
        });
    };

    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        std::vector<u64> vec;
        std::list<u64> list;
        std::deque<u64> deque;
        std::set<u64> set;
        std::unordered_set<u64> uset;
        std::map<u64, u64> map;
        std::unordered_map<u64, u64> umap;

        vec.reserve(size);

        while (uset.size() < size)
        {
            auto x = rng();
            if (uset.insert(x).second)
            {
                vec.push_back(x);
                list.push_back(x);
                deque.push_back(x);
                set.insert(x);
                map.emplace(x, x);
                umap.emplace(x, x);
            }
        }

        register_benchmark_auto(vec);
        register_benchmark_iterator(vec);

        register_benchmark_auto(list);
        register_benchmark_iterator(list);

        register_benchmark_auto(deque);
        register_benchmark_iterator(deque);

        register_benchmark_auto(set);
        register_benchmark_iterator(set);

        register_benchmark_auto(uset);
        register_benchmark_iterator(uset);

        register_benchmark_auto(map);
        register_benchmark_iterator(map);

        register_benchmark_auto(umap);
        register_benchmark_iterator(umap);
    }
}
