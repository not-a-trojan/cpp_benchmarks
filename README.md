# C++ Performance Benchmarks

**TL;DR** _This repository contains a number of benchmarks that compare relative performance for different data structures and algorithms across in use cases._ [benchmark results](results.md)

<br>

When looking for resources on parts of the C++ standard library, e.g., the STL containers or the `std::algorithm` library, one can select from a myriad of sources explaining the DOs and DON'Ts.

For example, a common advice on performance is that one can efficiently remove the last element from a `std::vector`, but removing the first one can be quite costly, since all remaining elements have to be moved.\
Likewise, one is often told that iterating a `std::vector` is faster than iterating the other container types of the STL, because of its cache-friendly contiguous memory layout.

While such statements are true, they do not convey how much faster or slower some of the most common operations are **in relation to each other**.\
Likewise, comparing big-O complexity of operations does not necessarily translate to real-world performance.

In fact, benchmarking and comparing said operations can yield surprising results!\
Take a look at this benchmark synopsys of iterating over the most common STL containers (<1x means faster than baseline, >1x means slower):

| iterating over 10'000 elements | clang++  | g++
|-------------------------------:|-----:|-----:|
| `std::vector<u64>` | 2.35 µs | 2.34 µs|
| `std::list<u64>` | 3.91x | 3.93x|
| `std::deque<u64>` | 1.07x | 1.07x|
| `std::set<u64>` | 21.90x | 23.21x|
| `std::unordered_set<u64>` | 3.91x | 4.02x|
| `std::map<u64, u64>` | 24.30x | 26.79x|
| `std::unordered_map<u64, u64>` | 4.86x | 3.96x|

<br>

While it was no surprise that iterating a `std::set` is slower than iterating a `std::vector`, I did not expect the set iteration to take more than 20x the time!

## **Note:** This should not be interpreted as a timing benchmark!

The provided benchmarks are **NOT** representative of actual timings in terms of "this takes *x* ns".
Timings highly depend on the surrounding application, overall system use, caches, and many other factors.
The sole purpose of this benchmark is to provide a feeling for **relative performance**.

Your take-home messages should be along the lines of _"Action A is roughly as fast as Action B, while Action C is much slower"_, not _"Action A takes exactly 23245 ns"_.

Also, keep in mind that many of these performance-relations become more pronounced (or even only become relevant) at large scale, hence the benchmarks are performed at increasingly larger container sizes.
In turn, when your project works with small containers, optimizing your code based on insights from these benchmarks likely won't have much of an impact.

<br>

# Results

This repository also contains results for all benchmarks on my machine (AMD Ryzen 7 3700X, 32GB RAM @ 3200 MHz) for both `g++ 9.3.0` and `clang++ 10.0.0`, executed in WSL.\
You can find the results [here](results.md).

<br>

# Build Instructions / Running the Benchmarks

I use [Google Benchmark](https://github.com/google/benchmark) for benchmarking.
On Linux, this can be installed easily via `sudo apt install libbenchmark-dev`.

1. Run `python3 run_benchmarks.py --benchmark g++ --benchmark clang++ --process-reports` (add/remove any compilers you want)
2. Grab a coffee, benchmarking might take a few minutes
3. Find your results in `results.md`

In case you want to execute specific benchmarks (e.g., when developing new benchmarks), proceed as follows:
1. Build benchmarks by running `make`
2. Execute your benchmark of choice directly from the `build` directory

<br>

# Contributing
I hope that this repository, over time, becomes a go-to source to get a feeling for relative performance of the most common standard library and STL use cases.

You can help by adding your own benchmarks via pull requests, reviewing existing benchmarks, and by noting bugs/ideas/suggestions/... via issues.
As a starting point for new benchmarks you can copy existing ones or take a look at [benchmark_template.cpp](benchmark_template.cpp)
