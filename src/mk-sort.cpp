
#include "../include/mk-sort.h"

#include <cstdio>
#include <vector>

static void printfVector(const std::vector<int> &v) {
    for (auto i : v) {
        printf("%d,", i);
    }

    printf("\n");
}

// 快速排序

static size_t partition(std::vector<int> &v, size_t left, size_t right) {
    size_t povit = (left + right) / 2;
    int value = v[povit];

    std::swap(v[povit], v[right]);

    int i = left;
    for (int j = left; j < right; j++) {
        if (v[j] < value) {
            std::swap(v[i++], v[j]);
        }
    }

    std::swap(v[i], v[right]);

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

static void printfVectorF(const std::vector<float> &v) {
    for (auto i : v) {
        printf("%f,", i);
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

static void BucketSort(std::vector<float> &nums) {
    int k = nums.size() / 2;
    std::vector<std::vector<float>> buckets(k);

    for (float num : nums) {
        int i = (int)(num * k);
        buckets[i].push_back(num);
    }
    for (auto &bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
    }
    int i = 0;
    for (auto &bucket : buckets) {
        for (auto v : bucket) {
            nums[i++] = v;
            ;
        }
    }
}

static void CountingSortNaive(std::vector<int> &nums) {
    int max = *std::max_element(nums.begin(), nums.end());
    std::vector<int> count(max + 1, 0);

    for (auto num : nums) {
        count[num]++;
    }

    int i = 0;

    for (int num = 0; num < max + 1; ++num) {
        for (int j = 0; j < count[num]; ++j, ++i) {
            nums[i] = num;
        }
    }
}

static int BinaryFind(const std::vector<int> &nums, const int val, const size_t left,
                      const size_t right) {
    if (left > right) {
        return -1;
    }

    int m = (right + left) / 2;

    return val == nums[m] ? m
                          : (val > nums[m] ? BinaryFind(nums, val, m + 1, right)
                                           : BinaryFind(nums, val, left, m - 1));
};

static void ArrangeData(std::vector<int> &nums, std::vector<int> &out) {}

void testSort() {
    std::vector<int> num = {5, 4, 3, 2, 1, 5, 2, 4};
    quickSort(num, 0, num.size() - 1);
    // partition(num, 0, num.size() - 1);
    printfVector(num);

    // auto a = rangeVector();

    //  printfVector(a);
    //  quickSort(a, (size_t)0, a.size() - 1);
    //  mergeSort(a, (size_t)0, a.size() - 1);
    //  printfVector(a);
    // Heap h = Heap::Make(rangeVector());
    // printfVector(h.toVector());
    // HeapSort(a);

    // std::vector<float> fNums = {0.1, 0.4, 0.2, 0.7, 0.3};
    // BucketSort(fNums);
    // printfVectorF(fNums);

    // std::vector<int> nums = {10, 20, 39, 53, 200};
    // printf("%d\n", BinaryFind(nums, 200, 0, nums.size() - 1));

    /*
      Link l;
      l.unShift(20);
      l.unShift(30);
      l.unShift(40);
      l.unShift(50);
      l.unShift(20);
      l.unShift(60);

      printfVector(l.toVector());
      l.del(60);
      // l.del(50);
      // l.del(20);
      printfVector(l.toVector());
    */
}
