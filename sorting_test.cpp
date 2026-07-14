// Validation harness for all sorting algorithms in this project.
// Implementation files are included directly so the suite builds as a single translation unit:
//   g++ -std=c++17 sorting_test.cpp -o build/sorting_test.exe

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "bubble_sort.cpp"
#include "cycle_sort.cpp"
#include "heap_sort.cpp"
#include "insertion_sort.cpp"
#include "merge_sort.cpp"
#include "selection_sort.cpp"

struct TestCase {
    std::string name;
    std::vector<int> input;
};

struct TestStats {
    int passed = 0;
    int failed = 0;

    void record_pass() { passed++; }
    void record_fail() { failed++; }
    int total() const { return passed + failed; }
};

std::string format_array(const std::vector<int> &values) {
    std::string result = "[";
    for (size_t i = 0; i < values.size(); i++) {
        if (i > 0) {
            result += ", ";
        }
        result += std::to_string(values[i]);
    }
    result += "]";
    return result;
}

std::vector<int> expected_sorted(const std::vector<int> &input) {
    std::vector<int> sorted = input;
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}

void report_failure(const std::string &algorithm_name,
                    const std::string &test_name,
                    const std::vector<int> &input,
                    const std::vector<int> &expected,
                    const std::vector<int> &actual) {
    std::cout << "[FAIL] " << algorithm_name << " - " << test_name << "\n";
    std::cout << "  Input:    " << format_array(input) << "\n";
    std::cout << "  Expected: " << format_array(expected) << "\n";
    std::cout << "  Actual:   " << format_array(actual) << "\n";
}

void run_sort_test(const std::string &algorithm_name,
                   const std::string &test_name,
                   const std::vector<int> &input,
                   const std::vector<int> &actual,
                   TestStats &stats) {
    const std::vector<int> expected = expected_sorted(input);

    if (actual == expected) {
        std::cout << "[PASS] " << algorithm_name << " - " << test_name << "\n";
        stats.record_pass();
        return;
    }

    report_failure(algorithm_name, test_name, input, expected, actual);
    stats.record_fail();
}

void run_array_sort_test(const std::string &algorithm_name,
                         const std::string &test_name,
                         const std::vector<int> &input,
                         void (*sort_fn)(int[], int),
                         TestStats &stats) {
    std::vector<int> actual = input;
    sort_fn(actual.data(), static_cast<int>(actual.size()));
    run_sort_test(algorithm_name, test_name, input, actual, stats);
}

void run_merge_sort_test(const std::string &test_name,
                         const std::vector<int> &input,
                         TestStats &stats) {
    std::vector<int> actual = input;
    if (!actual.empty()) {
        merge_sort(actual.data(), 0, static_cast<int>(actual.size()) - 1);
    }
    run_sort_test("merge_sort", test_name, input, actual, stats);
}

void run_cycle_sort_test(const std::string &test_name,
                         const std::vector<int> &input,
                         TestStats &stats) {
    std::vector<int> actual = input;
    cycle_sort(actual);
    run_sort_test("cycle_sort", test_name, input, actual, stats);
}

std::vector<TestCase> build_test_cases() {
    std::vector<TestCase> tests = {
        {"empty array", {}},
        {"single element", {42}},
        {"already sorted", {1, 2, 3, 4, 5}},
        {"reverse sorted", {9, 7, 5, 3, 1}},
        {"duplicates", {3, 1, 3, 2, 1, 3, 2}},
        {"negative numbers", {-5, 10, -3, 0, -8, 7, -1}},
    };

    // Fixed seed keeps random and large cases reproducible across runs.
    std::srand(42);

    std::vector<int> random_array;
    random_array.reserve(50);
    for (int i = 0; i < 50; i++) {
        random_array.push_back(std::rand() % 200 - 100);
    }
    tests.push_back({"random array", random_array});

    std::vector<int> large_array;
    large_array.reserve(5000);
    for (int i = 0; i < 5000; i++) {
        large_array.push_back(std::rand() % 100000 - 50000);
    }
    tests.push_back({"large array", large_array});

    return tests;
}

template <typename Runner>
void run_algorithm_suite(const std::string &algorithm_name,
                         const std::vector<TestCase> &tests,
                         TestStats &stats,
                         Runner runner) {
    std::cout << "--- " << algorithm_name << " ---\n";
    for (const TestCase &test : tests) {
        runner(test.name, test.input, stats);
    }
    std::cout << "\n";
}

int main() {
    const std::vector<TestCase> tests = build_test_cases();
    TestStats stats;

    std::cout << "=== Sorting Algorithm Validation ===\n";
    std::cout << "Algorithms: bubble_sort, selection_sort, insertion_sort, merge_sort, cycle_sort, heap_sort\n";
    std::cout << "Test cases: " << tests.size() << "\n\n";

    const std::pair<std::string, void (*)(int[], int)> array_sorters[] = {
        {"bubble_sort", bubble_sort},
        {"selection_sort", selection_sort},
        {"insertion_sort", insertion_sort},
        {"heap_sort", heap_sort},
    };

    for (const auto &sorter : array_sorters) {
        run_algorithm_suite(
            sorter.first,
            tests,
            stats,
            [&](const std::string &test_name, const std::vector<int> &input, TestStats &suite_stats) {
                run_array_sort_test(sorter.first, test_name, input, sorter.second, suite_stats);
            });
    }

    run_algorithm_suite("merge_sort", tests, stats, run_merge_sort_test);
    run_algorithm_suite("cycle_sort", tests, stats, run_cycle_sort_test);

    std::cout << "=== Summary ===\n";
    std::cout << "Total: " << stats.total()
              << "  Passed: " << stats.passed
              << "  Failed: " << stats.failed << "\n";

    return stats.failed > 0 ? 1 : 0;
}
