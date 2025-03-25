import os
import re
from collections import defaultdict

# Paths
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DATASTRUCTURES_DIR = os.path.join(BASE_DIR, "dataStructures")
ALGORITHMS_DIR = os.path.join(BASE_DIR, "algorithms")
TESTS_DIR = os.path.join(BASE_DIR, "tests")

def collect_cpp_basenames(directory):
    return {
        os.path.splitext(filename)[0]: os.path.join(directory, filename)
        for filename in os.listdir(directory)
        if filename.endswith(".hpp")
    }

data_files = collect_cpp_basenames(DATASTRUCTURES_DIR)
algo_files = collect_cpp_basenames(ALGORITHMS_DIR)

all_sources = {**data_files, **algo_files}
inclusion_counts = defaultdict(set)  # {filename: set of test files}

# Regex to extract includes like #include "something"
include_pattern = re.compile(r'#include\s+"([^"]+)"')

# Scan all test files
for test_file in os.listdir(TESTS_DIR):
    if not test_file.endswith(".cpp"):
        continue

    test_path = os.path.join(TESTS_DIR, test_file)
    with open(test_path, "r") as f:
        contents = f.read()
        includes = include_pattern.findall(contents)

        for inc in includes:
            base_name = os.path.splitext(os.path.basename(inc))[0]
            if base_name in all_sources:
                inclusion_counts[base_name].add(test_file)

# Write report
with open("README.md", "a+") as out:
    out.write("\nTest Coverage Report\n\n")
    for source_name in sorted(all_sources.keys()):
        count = len(inclusion_counts[source_name])
        if count >= 2:
            mark = "🟢"
        elif count == 1:
            mark = "🟡"
        else:
            mark = "🔴"
        out.write(f"{mark} {source_name}\n\n")
    out.write("---\n\n🟢 -> at least two tests\n\n🟡 -> only one test\n\n🔴 -> no tests\n\n")

print("✅ Test coverage report generated and saved in README.md")
