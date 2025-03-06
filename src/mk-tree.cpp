#include "../include/mk-tree.hpp"

#include <queue>

void testTree() {
    MkPileUp<int, std::greater<int>> minHeap;

    minHeap.from({30, 5, 20, 1, 560, 2});

    while (!minHeap.empty()) {
        printf("%d\t", minHeap.top());
        minHeap.pop();
    }

    printf("\n");
}
