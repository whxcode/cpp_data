#include <cmath>
#include <iostream>
#include <memory>
#include <set>

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

class A {};

static void test03() {
    std::weak_ptr<A> a1 = std::weak_ptr<A>();
    printf("[%d]\n", a1.expired());
    std::shared_ptr<A> a2 = std::make_shared<A>();
    a1 = a2;
    printf("[%d]\n", a1.expired());

    a1.reset();
    printf("[%d]\n", a1.expired());
}

class T {
public:
    virtual void show() = 0;
};

class C {
public:
    T *t;
};

class A1 : public T {
public:
    A1() {
        c = new C();
        c->t = this;
    }

public:
    void show() { printf("A\n"); };

public:
    C *c;
};

class B1 : public A1 {
public:
    void show() { printf("B\n"); };
};

static void test04() {
    B1 *b = new B1;
    b->c->t->show();
}

static void test05() {
    std::string v = "贵州省.svg";
    auto t = v.rfind(".svg");
}

static void test06() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b;
    b.resize(a.size());
    std::transform(a.begin(), a.end(), std::inserter(b, b.begin()), [](int v) { return v * 10; });

    for (const auto &v : b) {
        printf("pp [%d]\n", v);
    }
}

float binarySearch(const std::vector<float> &a, float v) {
    int i = 0;
    int j = a.size() - 1;

    while (i <= j) {
        int mid = i + (j - i) / 2;
        if (a[mid] == v) {
            return mid;
        }

        if (a[mid] < v) {
            i = mid + 1;
        }

        if (a[mid] > v) {
            j = mid - 1;
        }
    }

    return -1;
}

float binarySearchSet(const std::set<float> &a, float v) {
    auto i = a.begin();  // 设置指向容器开始的迭代器
    auto j = --a.end();  // 设置指向容器末尾的迭代器

    while (i != j) {
        // 计算中间迭代器
        auto mid = std::next(i, std::distance(i, j) / 2);

        if (*mid == v) {
            return *mid;  // 找到目标值，返回值
        }

        if (*mid < v) {
            i = std::next(mid);  // 如果中间值小于目标值，移动左指针
        } else {
            j = std::prev(mid);  // 如果中间值大于目标值，移动右指针
        }
    }

    // 最后检查 i 和 j 是否指向相同元素
    return (*i == v) ? *i : -1;  // 如果找到了目标值，返回；否则返回 -1
}

static void test07() {
    std::set<float> a = {1.0f, 2.0f, 3.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};

    for (int i = 0; i < 10 * 10 * 10 * 10; i++) {
        a.insert(i * 2);
    }

    for (const auto &v : a) {
        printf("a1[%f]\n", binarySearchSet(a, v));
    }
}

static void test08() {
    std::vector<float> a1 = {1, 3, 5, 7, 9};
    std::vector<float> a2 = {2, 4, 6, 8, 10};
    float e = 0.5;
    float value = 5.5;

    for (const auto &v : a1) {
        for (const auto &v2 : a2) {
            if (std::fabs((v + v2) / 2 - value) < e) {
                printf("ok\n");
            }
        }
    }

    printf("erorr\n");
}

int main() {
    // test08();
    // test06();
    // test05();
    // test04();
    // test03();
    // test02();
    return 0;
}
