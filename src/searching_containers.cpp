/*
This benchmark explores the differences in searching objects in containers.
All tests are performed with objects that exist as well as non-existing objects.
For sortable collections, both unsorted search and sorted binary search are included.
*/


#include "benchmark.h"
#include <algorithm>

template <bool BinarySearch, typename T>
void benchmark_instance(const T& collection, const std::vector<u64>& values, std::string title)
{
    benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
        auto size = values.size();
        for (auto _ : state)
        {
            state.PauseTiming();
            auto x = values[rng() % size];
            state.ResumeTiming();

            if constexpr (BinarySearch)
            {
                auto it = std::binary_search(collection.begin(), collection.end(), x);
                benchmark::DoNotOptimize(it);
            }
            else if constexpr (is_vector<T> || is_list<T> || is_deque<T>)
            {
                auto it = std::find(collection.begin(), collection.end(), x);
                benchmark::DoNotOptimize(it);
            }
            else
            {
                auto it = collection.find(x);
                benchmark::DoNotOptimize(it);
            }
        }
    });
}

template <typename T>
void benchmark_instance(const T& collection, const std::vector<u64>& values, std::string title)
{
    benchmark_instance<false, T>(collection, values, title);
}

void prepare_benchmarks()
{
    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        std::vector<u64> vec;
        std::vector<u64> vec_sorted;
        std::list<u64> list;
        std::list<u64> list_sorted;
        std::deque<u64> deque;
        std::deque<u64> deque_sorted;
        std::set<u64> set;
        std::unordered_set<u64> uset;
        std::map<u64, u64> map;
        std::unordered_map<u64, u64> umap;

        std::vector<u64> existing_values;
        std::vector<u64> non_existing_values;

        vec.reserve(size);
        existing_values.reserve(size);
        non_existing_values.reserve(size);

        while (uset.size() < size)
        {
            auto x = rng();
            if (uset.insert(x).second)
            {
                existing_values.push_back(x);

                vec.push_back(x);
                list.push_back(x);
                deque.push_back(x);
                set.insert(x);
                map.emplace(x, x);
                umap.emplace(x, x);
            }
        }

        {
            vec_sorted = vec;
            list_sorted = list;
            deque_sorted = deque;
            std::sort(vec_sorted.begin(), vec_sorted.end());
            list_sorted.sort();
            std::sort(deque_sorted.begin(), deque_sorted.end());
            while (non_existing_values.size() < size)
            {
                auto x = rng();
                if (!std::binary_search(vec_sorted.begin(), vec_sorted.end(), x))
                {
                    non_existing_values.push_back(x);
                }
            }
        }

        benchmark_instance(vec, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(vec) + " (unsorted)");
        benchmark_instance<true>(vec_sorted, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(vec_sorted) + " (sorted, binary search)");
        benchmark_instance(list, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(list) + " (unsorted)");
        benchmark_instance<true>(list_sorted, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(list_sorted) + " (sorted, binary search)");
        benchmark_instance(deque, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(deque) + " (unsorted)");
        benchmark_instance<true>(deque_sorted, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(deque_sorted) + " (sorted, binary search)");
        benchmark_instance(set, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(set));
        benchmark_instance(uset, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(uset));
        benchmark_instance(map, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(map));
        benchmark_instance(umap, existing_values, size_to_string(size) + " elements, searching random existing element; " + TypeName(umap));

        benchmark_instance(vec, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(vec) + " (unsorted)");
        benchmark_instance<true>(vec_sorted, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(vec_sorted) + " (sorted, binary search)");
        benchmark_instance(list, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(list) + " (unsorted)");
        benchmark_instance<true>(list_sorted, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(list_sorted) + " (sorted, binary search)");
        benchmark_instance(deque, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(deque) + " (unsorted)");
        benchmark_instance<true>(deque_sorted, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(deque_sorted) + " (sorted, binary search)");
        benchmark_instance(set, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(set));
        benchmark_instance(uset, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(uset));
        benchmark_instance(map, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(map));
        benchmark_instance(umap, non_existing_values, size_to_string(size) + " elements, searching random non-existing element; " + TypeName(umap));
    }
}
