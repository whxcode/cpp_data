#include "../include/mk-array.hpp"

#include <cmath>
#include <cstdio>
#include <set>

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
