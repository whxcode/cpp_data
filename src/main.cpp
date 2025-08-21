#include <chrono>
#include <cmath>

#include "../include/mk-pthread.h"

/*
struct Context {
    std::function<void()> f1{nullptr};
};

void setTimeout(std::function<void()> func, int delay_ms) {
    std::thread([func, delay_ms]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        func();
    }).detach();
}

void test(Context &&c) {
    // c++有没有类似于js的setTimeout机制.
    auto c_copy = std::make_shared<Context>(c);

    setTimeout(
        [c_copy]() mutable {
            std::cout << "Hello after 2 seconds!" << std::endl;
            c_copy->f1();
        },
        500);
    printf("test end\n");
}
*/

int main() {
    testPThread();

    /*
      uint8_t u = 1;
      uint8_t *pu = &u;

      for (int i = 0; i < 100; ++i) {
          int a[100] = {0};
      }

      int b = *(uint8_t *)(pu);

      printf("a = %d\n", b);
    */

    return 0;
}
