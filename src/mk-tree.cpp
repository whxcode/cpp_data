#include "../include/mk-tree.hpp"

#include <queue>
#include <unordered_map>

static void printfVector(const std::vector<int> &v) {
    for (auto i : v) {
        printf("%d,", i);
    }

    printf("\n");
}

std::vector<int> selectorSort(const std::vector<int> &vv) {
    auto v = vv;
    for (int i = 0; i < v.size(); ++i) {
        int k = i;
        for (int j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[k]) {
                k = j;
            }
        }
        std::swap(v[i], v[k]);
    }

    return v;
}

std::vector<int> bubbleSort(const std::vector<int> &vv) {
    auto v = vv;
    for (int i = v.size() - 1; i >= 0; --i) {
        bool exit = true;
        for (int j = 0; j < i; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                exit = false;
            }
        }

        if (exit) {
            break;
        }
    }
    return v;
}

std::vector<int> insertSort(const std::vector<int> &vv) {
    auto nums = vv;

    for (int i = 1; i < nums.size(); i++) {
        int base = nums[i];
        int j = i - 1;

        // 在已排序中
        while (j >= 0 && nums[j] > base) {
            nums[j + 1] = nums[j];
            j--;
        }

        nums[j + 1] = base;
    }

    return nums;
}

int partition(std::vector<int> &nums, int left, int right) {
    // 以 nums[left] 为基准数
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= nums[left]) {
            j--;
        };  // 从右向左找首个小于基准数的元素
        while (i < j && nums[i] <= nums[left]) {
            i++;
        };  // 从左向右找首个大于基准数的元素

        std::swap(nums[i], nums[j]);  // 交换两个元素
    }

    std::swap(nums[i], nums[left]);  // 交换基准数与最后一个小于基准数的元素
                                     //
    return i;                        // 返回基准数的索引
}

void quickSort(std::vector<int> &nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = partition(nums, left, right);
    // 递归左子数组、右子数组
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

void testTree() {
    printfVector(selectorSort({2, 1, -4, 2}));
    printfVector(bubbleSort({2, 1, -4, 2}));
    printfVector(insertSort({
        2,
        1,
        -4,
    }));

    std::vector<int> quickSortV = {2, 1, -4, 2};
    quickSort(quickSortV, 0, quickSortV.size() - 1);
    printfVector(quickSortV);

    // printf("sum[%d]\n", findTarget({1, 2, 3, 4, 5}, 3));
    // printf("sum[%d]\n", findTargetHash({1, 2, 3, 4, 5}, 3));

    /*
    printf("index[%d]\n", search({1, 2, 3, 4, 5}, 3));
    printf("index[%d]\n", search({1, 2, 3, 4, 5}, 5));
    printf("index[%d]\n", search({1, 2, 3, 4, 5}, 1));
    printf("searchIndex[%d]\n", searchIndexRight({2, 3, 3, 3, 4, 5}, 3));

      MkHeap heap;
      heap.push(10);
      heap.push(20);
      heap.push(5);
      heap.push(-2);

      while (!heap.empty()) {
          printf("[%d],", heap.peek());
          heap.pop();
      }

      printf("\n");
      */

    /*
      MkArrayTree tree;
      tree.push(10);
      tree.push(20);
      tree.push(30);
      tree.dfs(0);
    */

    // const char *str = "w";
    //  std::string b = str;
    //  ((void (*)(int a))0)(10);

    // std::cout << b << std::endl;
    // auto v = std::vector<int>{2, 1, -4, 2};
    // insertSort(v);
    // printfVector(v);

    // printf("11[%d]\n", arrayAtSum({1, 1, 10}, 11));
    // printf("11[%d]\n", arrayAtSum_v1({1, 1, 10}, 11));
}
