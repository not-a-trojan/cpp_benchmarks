#!/usr/bin/env python3

import sys
import os
import json
import re
import collections

def print_usage():
    print("Utility script to run and process benchmarks")
    print("Simply execute:")
    print("  python3 run_benchmarks.py [OPTIONS ...]")
    print("")
    print("Options:")
    print("  --help                   displays this message.")
    print("  --benchmark <compiler>   builds and executes all benchmarks for the given compiler.")
    print("                           provide this option multiple times to add more compilers.")
    print("  --filter <string>        only benchmark source files that contain the given string in their name.")
    print("  --process-reports        processes all generated reports and generates `results.md`.")
    print("")

# helper struct to hold all benchmark results that belong to the same group
# results_per_compiler is a dict from compiler name to a list of googlebenchmark json results
BenchmarkGroup = collections.namedtuple("BenchmarkGroup", ['title', 'results_per_compiler'])


# puts all words that contain '::' into backticks to get highlighted as code in markdown
def highlight_types(s):
    return re.sub( r"(\w+(::(\w|_)+)+(<.+?>)?)", r"`\1`", s)


# takes a nanosecond time and converts the timebase suffix to the best suitable
def format_time(t):
    n = 0
    suffixes = ['ns', 'µs', 'ms', 's']
    while t >= 1000 and n < len(suffixes) - 1:
        t /= 1000
        n += 1
    return f"{t:.2f} {suffixes[n]}"


# generates the actual benchmark tables and appends them to a specific file
def print_benchmarks(benchmark, noop, output_file):
    title = highlight_types(benchmark.title)
    compilers = sorted(benchmark.results_per_compiler.keys())
    num_results = len(benchmark.results_per_compiler[compilers[0]])

    # print table header
    line = f"| {title}"
    for compiler in compilers:
        line += f" | {compiler} "
    print(line, file=output_file)
    print( "|-" + "-"*len(title) + ":" + "|-----:" * len(compilers) + "|", file=output_file)

    # for every result index, iterate over all compiler results and print the respective table line
    baselines = dict()
    for result_index in range(num_results):

        # extract table line name (same for all compiler results, so just take it from the first one)
        result_name = benchmark.results_per_compiler[compilers[0]][result_index]["name"]
        result_name = result_name[len(benchmark.title)+1:].strip() # remove benchmark title prefix
        if "/iterations:" in result_name:
            result_name = result_name[:result_name.find("/iterations:")]
        result_name = highlight_types(result_name)

        line = f"| {result_name}"

        # format measured timings
        for compiler in compilers:
            time = float(benchmark.results_per_compiler[compiler][result_index]["cpu_time"])

            if result_index == 0:
                # first line is the baseline --> print timings
                baselines[compiler] = time
                line += f' | {format_time(time)}'
            else:
                # print other timings only relative to baseline
                change = time / baselines[compiler]
                line += f" | {change:.4f}x"

        print(line+"|", file=output_file)

    print("\n<br/><br/>\n", file=output_file)


# every benchmark cpp file can provide a description via a comment at the very top
# this gets extracted here and appended to a file
def print_description(filename, output_file):
    with open("src/" + filename[:filename.rfind(".")] + ".cpp") as cpp_file:
        in_description = False
        for line in cpp_file:
            line = line.strip()

            if not in_description:
                if not line: continue # skip leading empty lines

                if line.startswith("/*"):
                    in_description = True
                    print("<br/>\n", file=output_file)
                    line = line[line.find("/*") + 26:].strip()
                    if not line: continue
                else:
                    break # if there is anything else than a comment, exit

            if in_description: # explicitely not an 'else' to also process the first comment line
                if "*/" in line:
                    line = line[:line.find("*/")].strip()
                    if line:
                        print(highlight_types(line), file=output_file)
                    break
                else:
                    print(highlight_types(line) + "<br/>", file=output_file)

        print("<br/>\n", file=output_file)
        print("Baseline results (first line) report absolute CPU time.<br/>", file=output_file)
        print("All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>", file=output_file)
        print("<br/><br/>\n", file=output_file)



def process_reports():
    print("Processing reports...")

    if not os.path.isdir("reports/"):
        print("no report files found")
        return

    # collect all reports and verify that all compiler directories contain the same report files
    folders = sorted(os.listdir("reports/"))
    report_list = sorted(os.listdir(os.path.join("reports", folders[0])))
    if not all(report_list == sorted(os.listdir(os.path.join("reports", f))) for f in folders):
        print("Error: benchmark reports do not contain the same report files!")
        return

    with open("results.md", "wt") as output_file:
        for filename in report_list:

            # print headline
            converted_name = filename[:filename.rfind(".")].replace("_", " ").title()
            print(f"<details><summary>--- <b>{converted_name}</b> ---</summary>\n", file=output_file)

            print_description(filename, output_file)

            # go through the respective report file for every compiler and extract groups of benchmarks
            benchmark_groups = list()
            for folder in folders:
                current_file_path = os.path.join("reports/", folder, filename)
                print(f"Parsing '{current_file_path}'...")
                with open(current_file_path, "r") as read_file:
                    data = json.load(read_file)

                    current_title = None
                    current_results = list()
                    benchmark_counter = 0

                    # helper function to append recently parsed results to their benchmark group
                    def add_benchmark_group():
                        nonlocal benchmark_counter
                        if current_results:
                            if benchmark_counter >= len(benchmark_groups):
                                benchmark_groups.append(BenchmarkGroup(current_title, dict()))

                            if current_title != benchmark_groups[benchmark_counter].title:
                                print(f"Error: benchmarks are not aligned, trying to compare {current_title} with {benchmark_groups[benchmark_counter].title}")
                                return

                            benchmark_groups[benchmark_counter].results_per_compiler[folder] = current_results
                            benchmark_counter += 1


                    for result in data["benchmarks"]:
                        # benchmarks are grouped by common prefix before ';'
                        name_prefix = result["name"]
                        if ";" in name_prefix:
                            name_prefix = name_prefix[:name_prefix.index(";")]

                        if name_prefix != current_title:
                            add_benchmark_group()
                            current_title = name_prefix
                            current_results = list()

                        current_results.append(result)

                    add_benchmark_group()

            # check that the number of entries per group match across compilers
            for group in benchmark_groups:
                if any(len(r) != len(list(group.results_per_compiler.values())[0]) for r in group.results_per_compiler.values()):
                    print(f"Error: benchmark results for {group.title} do not contain the same amount of entries")
                    return

            # extract the NOOP benchmark if present
            noop = None
            for group in benchmark_groups:
                if group.title == "__BaselineNoop__":
                    benchmark_groups.remove(group)
                    noop = group
                    break

            print("Generating output...")
            for group in benchmark_groups:
                print_benchmarks(group, noop, output_file)

            print("</details>", file=output_file)
            print("Done!")


def run_benchmarks(compiler, name_filter):
    print(f"Running {compiler} benchmarks:")

    if os.system("make clean") != 0:
        return False

    if os.system(f"make -j CXX={compiler}") != 0:
        return False

    for benchmark in os.listdir("build"):
        if not name_filter or name_filter in benchmark:
            if os.system(f"build/{benchmark} --benchmark_out=reports/{compiler}/{benchmark}.json") != 0:
                return False

    print(f"{compiler} benchmarks done!\n")
    return True


if __name__ == "__main__":

    if len(sys.argv) == 1:
        print_usage()

    benchmarks_to_run = list()
    do_process_reports = False
    name_filter = None

    i = 1
    while i < len(sys.argv):

        if sys.argv[i] == "--help":
            print_usage()

        elif sys.argv[i] == "--benchmark":
            i += 1
            benchmarks_to_run.append(sys.argv[i])

        elif sys.argv[i] == "--filter":
            i += 1
            name_filter = sys.argv[i]

        elif sys.argv[i] == "--process-reports":
            do_process_reports = True

        else:
            print(f"skipping unknown '{sys.argv[i]}'")

        i += 1

    for b in set(benchmarks_to_run):
        if not run_benchmarks(b, name_filter):
            print("aborting benchmarks")
            sys.exit(1)

    if do_process_reports:
        process_reports()
