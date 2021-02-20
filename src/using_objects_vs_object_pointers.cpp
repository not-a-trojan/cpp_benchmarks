/*
This benchmark explores the difference in accessing "large" structs either directly or through smart/raw pointers to such objects.
*/

#include "benchmark.h"
#include <memory>

struct ThickObject
{
    std::array<u8, 128> values;
};

void benchmark_access(u64 size)
{
    {
        std::string title = "accessing " + size_to_string(size) + " objects (" + std::to_string(sizeof(ThickObject)) + " bytes each); access stack-allocated contiguous objects";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
            std::vector<ThickObject> objects;
            objects.reserve(size);
            for (u32 i = 0; i < size; ++i)
            {
                objects.push_back(ThickObject());
            }

            for (auto _ : state)
            {
                for (auto& o : objects)
                {
                    auto x = o.values[0];
                    benchmark::DoNotOptimize(x);
                }
            }
        });
    }

    {
        std::string title = "accessing " + size_to_string(size) + " objects (" + std::to_string(sizeof(ThickObject)) + " bytes each); access via raw pointers to heap-allocated objects";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
            std::vector<ThickObject*> heap_allocated_pointers;
            for (u32 i = 0; i < size; ++i)
            {
                heap_allocated_pointers.push_back(new ThickObject());
            }

            for (auto _ : state)
            {
                for (auto ptr : heap_allocated_pointers)
                {
                    auto x = ptr->values[0];
                    benchmark::DoNotOptimize(x);
                }
            }

            for (auto ptr : heap_allocated_pointers)
            {
                delete ptr;
            }
        });
    }

    {
        std::string title = "accessing " + size_to_string(size) + " objects (" + std::to_string(sizeof(ThickObject)) + " bytes each); access via unique pointers";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
            std::vector<std::unique_ptr<ThickObject>> unique_pointers;
            for (u32 i = 0; i < size; ++i)
            {
                unique_pointers.emplace_back(std::make_unique<ThickObject>());
            }

            for (auto _ : state)
            {
                for (auto& ptr : unique_pointers)
                {
                    auto x = ptr->values[0];
                    benchmark::DoNotOptimize(x);
                }
            }
        });
    }

    {
        std::string title = "accessing " + size_to_string(size) + " objects (" + std::to_string(sizeof(ThickObject)) + " bytes each); access via shared pointers";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) {
            std::vector<std::shared_ptr<ThickObject>> shared_pointers;
            for (u32 i = 0; i < size; ++i)
            {
                shared_pointers.emplace_back(std::make_shared<ThickObject>());
            }

            for (auto _ : state)
            {
                for (auto& ptr : shared_pointers)
                {
                    auto x = ptr->values[0];
                    benchmark::DoNotOptimize(x);
                }
            }
        });
    }
}

void benchmark_reordering(u64 size)
{
    {
        std::string title = "reordering " + size_to_string(size) + " objects (" + std::to_string(sizeof(ThickObject)) + " bytes each); shuffling objects";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) mutable {
            std::vector<ThickObject> objects;
            objects.reserve(size);
            for (u32 i = 0; i < size; ++i)
            {
                objects.push_back(ThickObject());
            }

            rng.seed(0);
            for (auto _ : state)
            {
                std::shuffle(objects.begin(), objects.end(), random_device);
            }
        });
    }

    {
        std::string title = "reordering " + size_to_string(size) + " objects (" + std::to_string(sizeof(ThickObject)) + " bytes each); shuffling raw pointers";
        benchmark::RegisterBenchmark(title.c_str(), [=](benchmark::State& state) mutable {
            std::vector<ThickObject*> ptrs;
            ptrs.reserve(size);
            for (u32 i = 0; i < size; ++i)
            {
                ptrs.push_back(nullptr);
            }

            rng.seed(0);
            for (auto _ : state)
            {
                std::shuffle(ptrs.begin(), ptrs.end(), random_device);
            }
        });
    }
}

void prepare_benchmarks()
{
    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        benchmark_access(size);
    }
    for (unsigned size : {10'000, 100'000, 1'000'000})
    {
        benchmark_reordering(size);
    }
}
