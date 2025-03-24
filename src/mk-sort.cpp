
#include "../include/mk-sort.h"

#include <cstdio>
#include <vector>

// 快速排序

// 找到满足  left < i < right
size_t partition(std::vector<int> &v, size_t left, size_t right) {
    int i = left, j = right;
    while (i < j) {
        while (i < j && v[j] >= v[left]) {
            j--;
        }

        while (i < j && v[i] <= v[left]) {
            i++;
        }

        std::swap(v[i], v[j]);
    }

    // 将 left 放到 i 位置
    std::swap(v[left], v[i]);

    return i;
}

void quickSort(std::vector<int> &v, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t povit = partition(v, left, right);
    quickSort(v, left, povit - 1);
    quickSort(v, povit + 1, right);
}

void merge(std::vector<int> &nums, size_t left, size_t mid, size_t right) {
    std::vector<int> tmp(right - left + 1);

    size_t i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            tmp[k++] = nums[i++];
        } else {
            tmp[k++] = nums[j++];
        }
    }

    while (i <= mid) {
        tmp[k++] = nums[i++];
    }

    while (j <= right) {
        tmp[k++] = nums[j++];
    }

    for (size_t k = 0; k < tmp.size(); k++) {
        nums[left + k] = tmp[k];
    }
}

void mergeSort(std::vector<int> &v, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t mid = (left + right) / 2;
    mergeSort(v, left, mid);
    mergeSort(v, mid + 1, right);

    merge(v, left, mid, right);
}

std::vector<int> rangeVector() {
    int n = 10;
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        // 生成 [-10,10] 的随机数
        a.push_back(rand() % 20 - 10);
    }
    return a;
}

static void printfVector(const std::vector<int> &v) {
    for (auto i : v) {
        printf("%d,", i);
    }

    printf("\n");
}

static void ShiftDown(std::vector<int> &v, const size_t size, const int index) {
    int i = index;

    while (true) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int m = i;

        if (left < size && v[m] <= v[left]) {
            m = left;
        }

        if (right < size && v[m] <= v[right]) {
            m = right;
        }

        if (m == i) {
            break;
        }

        std::swap(v[m], v[i]);
        i = m;
    }
}

static void HeapSort(std::vector<int> &v) {
    for (int i = v.size() / 2 - 1; i >= 0; i--) {
        ShiftDown(v, v.size(), i);
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        std::swap(v[0], v[i]);
        ShiftDown(v, i, 0);
    }

    printfVector(v);
}

void testSort() {
    auto a = rangeVector();
    //  printfVector(a);
    //  quickSort(a, (size_t)0, a.size() - 1);
    //  mergeSort(a, (size_t)0, a.size() - 1);
    //  printfVector(a);
    // Heap h = Heap::Make(rangeVector());
    // printfVector(h.toVector());
    HeapSort(a);
}
