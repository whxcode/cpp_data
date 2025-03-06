#include "../include/mk-array.hpp"

#include <cmath>
#include <cstdio>
#include <deque>

struct MkMeasureScalar {
public:
    MkMeasureScalar(float value, float lower, float upper)
        : value(value), lower(lower), upper(upper) {}

    // 重载 operator< 以实现排序和唯一性
    bool operator<(const MkMeasureScalar& other) const {
        // 如果两个值的差值小于 0.000001，则认为它们相等
        if (std::fabs(value - other.value) < 0.000001) {
            return false;  // 返回 false 表示相等
        }
        return value < other.value;  // 否则按 value 排序
    }

public:
    float value{0};
    float lower{0};
    float upper{0};
};

void mkArrayTest() {
    MkDbLink link;
    link.push(10);
    link.push(20);
    link.push(30);

    while (!link.empty()) {
        link.shift();
        // printf("link[%d]\n", link.shift());
    }

    printf("\n");

    link.unShift(10);
    link.unShift(20);
    link.unShift(30);

    while (!link.empty()) {
        printf("link[%d]\n", link.shift());
    }

    /*
    std::deque<int> dogs;
    dogs.push_back(10);
    dogs.push_back(20);
    printf("dogs[%d]\n", dogs.back());

    // [0,0,0,0]
    // [10,20,0,0]
    ArrayQueue queue(4);
    queue.push(10);  //
    queue.push(20);

    printf("queue[%d]\n", queue.pop());
    // [0,20,0,0]
    // 1,2
    queue.push(30);

    // [50,20,30,40]
    queue.push(40);
    queue.push(50);
    queue.push(60);

    while (!queue.isEmpty()) {
        printf("queue[%d]\t", queue.pop());
    }

    printf("\n");
    for (size_t i = 0; i < queue.capacity(); ++i) {
        queue.push((i + 1) * 10);
    }

    while (!queue.isEmpty()) {
        printf("queue[%d]\t", queue.pop());
    }

    printf("\n");

    MkLinkedStack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    printf("stack.isEmpty()[%d]\n", stack.isEmpty());

    while (!stack.isEmpty()) {
        printf("[%d]\n", stack.pop());
    }

      MkList l;
      l.insert(10);
      l.insert(20);
      l.insert(30);
      l.insert(40);
      l.each();

      MkStack stack;
      stack.insert(10);
      stack.insert(20);
      stack.insert(30);
      stack.insert(40);

      while (!stack.empty()) {
          printf("[[%d]]\n", stack.pop());
      }
    */

    /*
      std::set<MkMeasureScalar> dogs;
      dogs.insert({1, 1, 1});
      dogs.insert({1.2, 1, 1});
      dogs.insert({1, 1, 1});

      printf("MkArrayTest[%ld]\n", dogs.size());
      for (auto dog : dogs) {
          printf("MkArrayTest[%f]\n", dog.value);
      }
       MkArray<int> dogs(10);
       dogs[0];
    */
}
