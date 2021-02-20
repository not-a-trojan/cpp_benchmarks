/*
This benchmark explores the differences in removing the first/last/random element from various STL containers.
*/

#include "benchmark.h"
#include <algorithm>

template <typename T, typename R>
static void reinsert(T& v, R x)
{
    if constexpr (is_vector<T> || is_list<T> || is_deque<T>)
    {
        v.push_back(x);
    }
    else if constexpr (is_set<T>)
    {
        v.insert(x);
    }
    else
    {
        v.emplace(x, x);
    }
}

template <typename T, typename IT>
static auto extract(T& collection, IT& it)
{
    if constexpr (is_map<decltype(collection)>)
    {
        return it->first;
    }
    else
    {
        return *it;
    }
}

void prepare_benchmarks()
{
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

        auto register_first_benchmark = [=](auto& collection) {
            std::string title = size_to_string(size) + " elements; erase first element from " + TypeName(collection);
            benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) mutable {
                u64 to_remove = 0;
                for (auto _ : state)
                {
                    state.PauseTiming();
                    reinsert(collection, to_remove);
                    auto it = collection.begin();
                    to_remove = extract(collection, it);
                    state.ResumeTiming();

                    collection.erase(it);
                }
                reinsert(collection, to_remove);
            });
        };

        auto register_last_benchmark = [=](auto& collection) {
            std::string title = size_to_string(size) + " elements; erase last element from " + TypeName(collection);
            benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) mutable {
                u64 last_value = 0;

                if constexpr (is_unordered<decltype(collection)>)
                {
                    auto it = collection.begin();
                    std::advance(it, collection.size() - 1);
                    last_value = extract(collection, it);
                }
                else
                {
                    auto it = std::next(collection.rbegin()).base(); // much faster than std::advance from begin(), use if available
                    last_value = extract(collection, it);
                }

                auto it = collection.begin();
                for (auto _ : state)
                {
                    state.PauseTiming();
                    reinsert(collection, last_value);
                    if constexpr (is_vector<decltype(collection)> || is_list<decltype(collection)> || is_deque<decltype(collection)>)
                    {
                        it = std::next(collection.rbegin()).base();
                    }
                    else
                    {
                        it = collection.find(last_value);
                    }
                    state.ResumeTiming();

                    collection.erase(it);
                }
                reinsert(collection, last_value);
            });
        };

        auto register_random_benchmark = [=](auto& collection) {
            std::string title = size_to_string(size) + " elements; erase random element from " + TypeName(collection);
            return benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) mutable {
                u64 to_remove = 0;
                auto it = collection.begin();
                for (auto _ : state)
                {
                    state.PauseTiming();
                    reinsert(collection, to_remove);
                    if constexpr (is_vector<decltype(collection)>)
                    {
                        it = collection.begin() + (rng() % size);
                    }
                    else if constexpr (is_list<decltype(collection)> || is_deque<decltype(collection)>)
                    {
                        it = collection.begin();
                        std::advance(it, (rng() % size));
                    }
                    else
                    {
                        it = collection.find(vec[rng() % size]);
                    }
                    to_remove = extract(collection, it);
                    state.ResumeTiming();

                    collection.erase(it);
                }
                reinsert(collection, to_remove);
            });
        };

        register_random_benchmark(vec);
        register_first_benchmark(vec);
        register_last_benchmark(vec);

        register_random_benchmark(list)->Iterations(100'000); // limit iterations to avoid extreme test duration
        register_first_benchmark(list);
        register_last_benchmark(list);

        register_random_benchmark(deque);
        register_first_benchmark(deque);
        register_last_benchmark(deque);

        register_random_benchmark(set);
        register_first_benchmark(set);
        register_last_benchmark(set);

        register_random_benchmark(uset);
        register_first_benchmark(uset);
        register_last_benchmark(uset);

        register_random_benchmark(map);
        register_first_benchmark(map);
        register_last_benchmark(map);

        register_random_benchmark(umap);
        register_first_benchmark(umap);
        register_last_benchmark(umap);
    }
}
