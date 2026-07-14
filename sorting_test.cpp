#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "bubble_sort.cpp"
#include "insertion_sort.cpp"
void merge(int arr[], int l, int mid, int r);
#include "merge_sort.cpp"
#include "selection_sort.cpp"
#include "cycle_sort.cpp"

struct TestCase {
    std::string name;
    std::vector<int> input;
};

std::string format_array(const std::vector<int> &arr) {
    std::string result = "[";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i > 0) {
            result += ", ";
        }
        result += std::to_string(arr[i]);
    }
    result += "]";
    return result;
}

std::vector<int> expected_sorted(const std::vector<int> &input) {
    std::vector<int> sorted = input;
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}

void run_array_sort_test(const std::string &algorithm_name,
                         const std::string &test_name,
                         const std::vector<int> &input,
                         void (*sort_fn)(int[], int),
                         int &pass_count,
                         int &fail_count) {
    std::vector<int> actual = input;
    sort_fn(actual.data(), static_cast<int>(actual.size()));

    std::vector<int> expected = expected_sorted(input);
    if (actual == expected) {
        std::cout << "[PASS] " << algorithm_name << " - " << test_name << "\n";
        pass_count++;
    } else {
        std::cout << "[FAIL] " << algorithm_name << " - " << test_name << "\n";
        std::cout << "  Input:    " << format_array(input) << "\n";
        std::cout << "  Expected: " << format_array(expected) << "\n";
        std::cout << "  Actual:   " << format_array(actual) << "\n";
        fail_count++;
    }
}

void run_merge_sort_test(const std::string &test_name,
                         const std::vector<int> &input,
                         int &pass_count,
                         int &fail_count) {
    std::vector<int> actual = input;
    if (!actual.empty()) {
        merge_sort(actual.data(), 0, static_cast<int>(actual.size()) - 1);
    }

    std::vector<int> expected = expected_sorted(input);
    if (actual == expected) {
        std::cout << "[PASS] merge_sort - " << test_name << "\n";
        pass_count++;
    } else {
        std::cout << "[FAIL] merge_sort - " << test_name << "\n";
        std::cout << "  Input:    " << format_array(input) << "\n";
        std::cout << "  Expected: " << format_array(expected) << "\n";
        std::cout << "  Actual:   " << format_array(actual) << "\n";
        fail_count++;
    }
}

void run_cycle_sort_test(const std::string &test_name,
                         const std::vector<int> &input,
                         int &pass_count,
                         int &fail_count) {
    std::vector<int> actual = input;
    cycle_sort(actual);

    std::vector<int> expected = expected_sorted(input);
    if (actual == expected) {
        std::cout << "[PASS] cycle_sort - " << test_name << "\n";
        pass_count++;
    } else {
        std::cout << "[FAIL] cycle_sort - " << test_name << "\n";
        std::cout << "  Input:    " << format_array(input) << "\n";
        std::cout << "  Expected: " << format_array(expected) << "\n";
        std::cout << "  Actual:   " << format_array(actual) << "\n";
        fail_count++;
    }
}

std::vector<TestCase> build_test_cases() {
    std::vector<TestCase> tests;

    tests.push_back({"empty array", {}});
    tests.push_back({"single element", {42}});
    tests.push_back({"already sorted", {1, 2, 3, 4, 5}});
    tests.push_back({"reverse sorted", {9, 7, 5, 3, 1}});
    tests.push_back({"duplicates", {3, 1, 3, 2, 1, 3, 2}});
    tests.push_back({"negative numbers", {-5, 10, -3, 0, -8, 7, -1}});

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

int main() {
    std::vector<TestCase> tests = build_test_cases();
    int pass_count = 0;
    int fail_count = 0;

    std::cout << "=== Sorting Algorithm Validation ===\n";
    std::cout << "Algorithms: bubble_sort, selection_sort, insertion_sort, merge_sort, cycle_sort\n";
    std::cout << "Test cases: " << tests.size() << "\n\n";

    const std::pair<std::string, void (*)(int[], int)> array_sorters[] = {
        {"bubble_sort", bubble_sort},
        {"selection_sort", selection_sort},
        {"insertion_sort", insertion_sort},
    };

    for (const auto &sorter : array_sorters) {
        std::cout << "--- " << sorter.first << " ---\n";
        for (const TestCase &test : tests) {
            run_array_sort_test(sorter.first, test.name, test.input, sorter.second,
                                pass_count, fail_count);
        }
        std::cout << "\n";
    }

    std::cout << "--- merge_sort ---\n";
    for (const TestCase &test : tests) {
        run_merge_sort_test(test.name, test.input, pass_count, fail_count);
    }
    std::cout << "\n";

    std::cout << "--- cycle_sort ---\n";
    for (const TestCase &test : tests) {
        run_cycle_sort_test(test.name, test.input, pass_count, fail_count);
    }
    std::cout << "\n";

    std::cout << "=== Summary ===\n";
    std::cout << "Total: " << (pass_count + fail_count)
              << "  Passed: " << pass_count
              << "  Failed: " << fail_count << "\n";

    return fail_count > 0 ? 1 : 0;
}
