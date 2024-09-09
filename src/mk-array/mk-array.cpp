#include "../../include/mk-array/mk-array.hpp"

#include <iostream>

#include "../../include/mk-array/mk-list.hpp"
#include "../../include/mk-array/mk-stack.hpp"

void MkArrayTest() {
    size_t SIZE = 10;
    MkArray<int> dogs(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        dogs[i] = i * 100;
    }

    dogs(2) = -1;
    dogs(0) = -50;

    for (int i = 0; i < SIZE; ++i) {
        printf("%d\n", dogs[i]);
    }

    auto t = dogs.map<double>([](int v) -> double { return v * 0.5; });
    t->foreach ([](double v) { printf("%f\n", v); });

    std::cout << "tt:" << t->at(-1) << std::endl;
    std::cout << "tt-i:" << t->find(t->at(-1)) << std::endl;

    t->extends(2);

    t->foreach ([](double v) { printf("%f\n", v); });
}

void MkArrayList() {
    MkList<int> list;
    list.push(100);
    list.push(200);
    list.insert(50, 1);
    list.insert(1000, 3);
    list.insert(3000, 3);

    std::cout << "size:" << list.getSize() << std::endl;

    list.foreach ([](int v) { printf("%d\n", v); });

    list.map<double>([](int v) -> double { return v * 1.5; })->foreach ([](double v) {
        printf("%f\n", v);
    });

    list.map<std::string>([](int v) { return "whx" + std::to_string(v); })
        ->foreach ([](std::string v) { printf("%s\n", v.c_str()); });

    // list.detach(1);
    // list.detach(0);
    // list.detach(0);
    // list.detach(0);

    // list.foreach ([](int v) { printf("%d\n", v); });
    // std::make_index_sequence
    // std::make_shared<B>();
    // std::cout << "MkArrayList" << std::endl;
}

void MkStackTest() {
    MkStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "isEmpty:" << stack.isEmpty() << std::endl;

    while (!stack.isEmpty()) {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }
}
