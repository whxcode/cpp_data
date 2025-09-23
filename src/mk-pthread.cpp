#include "../include/mk-pthread.h"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>

static void output() {
    std::ofstream ofs("/home/whx/study/data_cpp/src/temp.txt", std::ios::out | std::ios::trunc);
    if (!ofs) {
        std::cerr << "Error: Could not create temp.txt" << std::endl;
        return;
    }
    ofs << "Hello World" << std::endl;
    ofs.close();
    std::cout << "temp.txt created and written successfully." << std::endl;
}

class Bg {
public:
    void operator()() const { printf("operator\n"); }
    ~Bg() { printf("~~~~\n"); }
};

class Func {
public:
    Bg &i;
    Func(Bg &i) : i(i) {}
    void operator()() {
        for (int j = 0; j < 10; ++j) {
            // printf("访问\n");
            std::this_thread::sleep_for(std::chrono::microseconds(1));  // 等待子线程完成
                                                                        // printf("%d\n", i);
        }
    }
};

static void test01() {
    Bg i;
    Func func(i);
    std::thread t(func);
    try {
        printf("-----------\n");
        throw std::runtime_error("error");
    } catch (...) {
        t.join();
        printf("xxxxxxxxxxxxxxxx\n");
        throw;
    }

    t.join();
}

class ThreadGuard {
public:
    std::thread &t;
    explicit ThreadGuard(std::thread &t) : t(t) {}
    ~ThreadGuard() {
        if (t.joinable()) {
            t.join();
            printf("joble\n");
        }
    }
    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard &operator=(ThreadGuard const &) = delete;
};

static void test02() {
    Bg i;
    Func func(i);
    std::thread t(func);
    ThreadGuard tg(t);

    printf("-----------\n");
    throw std::runtime_error("error");
}

static void f1(const size_t i) {
    std::cout << "i->" << i << ":" << std::this_thread::get_id() << std::endl;
}

static void test03() {
    printf("std::thread::hardware_concurrency(%lu)\n", std::thread::hardware_concurrency());
    std::vector<std::thread> threads;

    for (size_t i = 0; i < 20; ++i) {
        threads.push_back(std::thread(f1, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

// 共享数据
int count = 0;
static void f2() {
    /*
      std::lock_guard<std::mutex> lock(mtx);  // 1
      for (int i = 0; i < 1000; ++i) {
          std::lock_guard<std::mutex> lock(mtx);  // 2
          ++count;
      }
      */
}

static void test04() {
    std::vector<std::thread> threads;

    // 创建 10 个线程，每个线程自增 1000 次
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(f2);
    }

    for (auto &t : threads) {
        t.join();
    }

    printf("[%d]count[%d]\n", 0, count);
}

std::list<int> list;
std::mutex mtx;  // 互斥锁

void addToList() {
    for (int i = 0; i < 1000; i++) {
        std::lock_guard<std::mutex> lock(mtx);  // 自动加锁和解锁
        list.push_back(i);
    }
}

bool listContains(int value) {
    std::lock_guard<std::mutex> lock(mtx);  // 自动加锁和解锁
    return std::find(list.begin(), list.end(), value) != list.end();
}

static void test05() {
    std::vector<std::thread> threads;

    // 创建 10 个线程，每个线程自增 1000 次
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(addToList);
    }

    for (auto &t : threads) {
        t.join();
    }

    printf("[%d]count[%lu]\n", 0, list.size());
}

std::mutex mtx1;
std::mutex mtx2;

void threadA() {
    std::lock_guard<std::mutex> lock1(mtx1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 增加死锁概率
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "Thread A finished\n";
}

void threadB() {
    std::lock_guard<std::mutex> lock2(mtx2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 增加死锁概率
    std::lock_guard<std::mutex> lock1(mtx1);
    std::cout << "Thread B finished\n";
}

static void test06() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();
}

// 简单base64编码实现
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static std::string base64_encode(const std::vector<unsigned char> &bytes) {
    std::string ret;
    int i = 0;
    unsigned char char_array_3[3], char_array_4[4];
    size_t len = bytes.size();
    size_t pos = 0;

    while (len--) {
        char_array_3[i++] = bytes[pos++];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; i < 4; i++) ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for (int j = i; j < 3; j++) char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (int j = 0; j < i + 1; j++) ret += base64_chars[char_array_4[j]];
        while (i++ < 3) ret += '=';
    }
    return ret;
}

void f3() {
    // 读取文件内容,转为base64内容.txt
    std::string home = std::getenv("HOME");
    std::string path = home + "/webProject/mk-app/modules/uikit/npm_build/libs/canvaskit.wasm";

    // 读取文件内容
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)),
                                      std::istreambuf_iterator<char>());

    // base64编码
    std::string encoded = base64_encode(buffer);

    std::thread::id tid = std::this_thread::get_id();
    std::ostringstream oss;
    oss << tid;
    std::string tid_str = oss.str();

    // 写入base64内容.txt
    std::ofstream out(home + "/study/data_cpp/base64/" + tid_str);
    if (!out) {
        std::cerr << "Failed to write output file." << std::endl;
        return;
    }
    out << encoded;
    out.close();
}

static void test07() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(f3);
    }

    for (auto &t : threads) {
        t.join();
    }
}

void testPThread() {
    int a = 100;
    printf("%f\n", a);
    // test07();
    // test06();
    // test04();
    // test03();
    // test02();
    // test01();
    // test01();
    // std::this_thread::sleep_for(std::chrono::seconds(2));  // 等待子线程完成
    /*
      Bg bg;
      std::thread t((Bg()));
      t.join();
    */
}
