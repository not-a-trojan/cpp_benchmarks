/*
A typical situation is filtering a list of elements, only keeping unique ones.
While a std::set or std::unordered_set does just that, it may be preferable to use a std::vector instead and delete duplicates in the end.

This benchmark explores the differences in various approaches to solve said task, for several levels of collision.
p% collision means that out of the inserted values p% of the values appear more than once and thus have to be filtered out.
*/

#include "benchmark.h"
#include <algorithm>
#include <random>

void prepare_benchmarks()
{
    std::default_random_engine engine;

    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        for (float percent_collisions : {0.f, 0.25f, 0.5f, 0.75f, 1.f})
        {
            std::vector<u64> numbers;
            numbers.reserve(size);

            if (percent_collisions != 1.f)
            {
                std::unordered_set<u64> unique_numbers;
                while (unique_numbers.size() <= (size - 1) * (1. - percent_collisions))
                {
                    unique_numbers.insert(rng());
                }

                numbers.reserve(size);
                numbers.insert(numbers.end(), unique_numbers.begin(), unique_numbers.end());

                while (numbers.size() < size)
                {
                    numbers.push_back(numbers[rng() % numbers.size()]);
                }
            }
            else
            {
                numbers.assign(size, rng());
            }

            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::vector<u64>, elements added all at once";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::vector<u64> vec = numbers;
                        std::sort(vec.begin(), vec.end());
                        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
                        benchmark::DoNotOptimize(vec);
                    }
                });
            }

            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::vector<u64>, elements added one-by-one, filtered in the end";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::vector<u64> vec;
                        for (auto& x : numbers)
                            vec.push_back(x);
                        std::sort(vec.begin(), vec.end());
                        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

                        benchmark::DoNotOptimize(vec);
                    }
                });
            }

            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::vector<u64>, elements added one-by-one, filtered halfway and in the end";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, size, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::vector<u64> vec;

                        for (size_t i = 0; i < size / 2; ++i)
                        {
                            vec.push_back(numbers[i]);
                        }

                        std::sort(vec.begin(), vec.end());
                        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

                        for (size_t i = size / 2; i < size; ++i)
                        {
                            vec.push_back(numbers[i]);
                        }

                        std::sort(vec.begin(), vec.end());
                        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

                        benchmark::DoNotOptimize(vec);
                    }
                });
            }

            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::set<u64>, elements added all at once";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::set<u64> set(numbers.begin(), numbers.end());

                        benchmark::DoNotOptimize(set);
                    }
                });
            }

            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::set<u64>, elements added one-by-one";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::set<u64> set;
                        for (auto& x : numbers)
                            set.insert(x);

                        benchmark::DoNotOptimize(set);
                    }
                });
            }

            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::unordered_set<u64>, elements added all at once";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::unordered_set<u64> set(numbers.begin(), numbers.end());

                        benchmark::DoNotOptimize(set);
                    }
                });
            }
            {
                std::string title = "inserting " + size_to_string(size) + " elements, " + std::to_string((int)(percent_collisions * 100)) + "% collision; using std::unordered_set<u64>, elements added one-by-one";
                benchmark::RegisterBenchmark(title.c_str(), [numbers, engine](benchmark::State& state) mutable {
                    for (auto _ : state)
                    {
                        state.PauseTiming();
                        std::shuffle(numbers.begin(), numbers.end(), engine);
                        state.ResumeTiming();

                        std::unordered_set<u64> set;
                        for (auto& x : numbers)
                            set.insert(x);

                        benchmark::DoNotOptimize(set);
                    }
                });
            }
        }
    }
}
