#include <iostream>

#include "../include/mk-array/mk-array.hpp"
#include "../include/mk-array/mk-list.hpp"
#include "../include/mk-array/mk-stack.hpp"
#include "../include/mk-auto.h"

auto f1(int a, int b) -> decltype(a) {
    int *c = new int;

    return *c;
}

auto f2(int a, int b) -> decltype((a)) {
    int *c = new int;

    return *c;
}

static void test01() {
    std::cout << std::is_same<int, short>::value << std::endl;
}

template <typename T>
auto add(const T &v) {
    if constexpr (std::is_integral<T>::value) {
        return v + 1;
    }

    if constexpr (std::is_floating_point<T>::value) {
        return v + 1.02;
    }
}

static void test02() {
    std::function<void(int a, int b)> f1 = [](int a, int b) {
        std::cout << "a> b" << (a > b) << ::std::endl;
    };

    f1(10, 20);
    // 交换参数位置
    std::bind(f1, std::placeholders ::_2, std::placeholders ::_1)(10, 20);
}

int main() {
    test02();
    return 0;
}
