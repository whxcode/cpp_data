#include "../include/mk-pthread.h"

static void output(int i) {
    std::cout << i << std::endl;
}

void testPThread() {
    for (size_t i = 0; i < 4; ++i) {
        std::thread t(output, i);
        t.detach();
    }

    getchar();
}
