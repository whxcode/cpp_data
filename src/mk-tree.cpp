#include "../include/mk-tree.hpp"

#include <queue>

void testTree() {
    /*
      std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
      minHeap.push(10);
      minHeap.push(20);
      minHeap.push(30);
      minHeap.push(5);

      std::cout << "o:" << minHeap.top() << std::endl;
      */

    /*
      MkBinSearchTree<int> tree;
        tree.add(10);
        tree.add(20);
        tree.add(30);
        tree.add(5);

      tree.push(10);
      tree.push(20);
      tree.push(30);
      tree.push(5);

      tree.inOrderTraversal([](const int &v) { printf("%d\t", v); });
      printf("\n");

      std::cout << "height:" << tree.height() << std::endl;
      std::cout << "height_V2:" << tree.heightV2() << std::endl;

      printf("target (30)(%p)\n", tree.find(30));
      printf("target (4)(%p)\n", tree.find(4));

    */

    MkPileUp<int, std::less<int>> minHeap;

    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(20);
    minHeap.push(5);

    while (!minHeap.empty()) {
        printf("%d\t", minHeap.top());
        minHeap.pop();
    }

    printf("\n");
}
