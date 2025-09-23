#include "../include/coroutines.hpp"

#include <algorithm>
#include <coroutine>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>

class IntReader {
public:
    void BeginRead(const std::function<void(int)>& callback) {
        std::thread thread([callback]() {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int value = std::rand() / 10000000;

            callback(value);
        });

        thread.detach();
    }
};

void printIntV2() {
    IntReader reader1;
    reader1.BeginRead([](int result1) {
        int total = result1;

        IntReader reader2;
        reader2.BeginRead([total](int result2) mutable {
            total += result2;

            IntReader reader3;
            reader3.BeginRead([total](int result3) mutable {
                total += result3;
                std::cout << "total: " << total << std::endl;
            });
        });
    });
}

// ========================= co_await ==================
class IntReaderA {
public:
    bool await_ready() { return false; }

    void await_suspend(std::coroutine_handle<> handle) {
        std::thread thread([this, handle]() {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            value_ = std::rand();

            handle.resume();
        });

        thread.detach();
    }

    int await_resume() { return value_; }

private:
    int value_{};
};

class Task {
public:
    class promise_type {
    public:
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
    };
};

Task printIntV3() {
    IntReaderA reader1;
    int total = co_await reader1;

    IntReaderA reader2;
    total += co_await reader2;

    IntReaderA reader3;
    total += co_await reader3;

    std::cout << "total:" << total << std::endl;
}

// ========================= co_return ==================
class IntReaderB {
public:
    bool await_ready() { return false; }

    void await_suspend(std::coroutine_handle<> handle) {
        std::thread thread([this, handle]() {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            value_ = std::rand();

            handle.resume();
        });

        thread.detach();
    }

    int await_resume() { return value_; }

private:
    int value_{};
};

class TaskB {
public:
    class promise_type {
    public:
        promise_type() : value_(std::make_shared<int>(0)) {}

        TaskB get_return_object() { return TaskB{value_}; }

        std::suspend_never initial_suspend() { return {}; }

        std::suspend_never final_suspend() noexcept { return {}; }

        void return_value(int value) { *value_ = value; }

        void unhandled_exception() {}

    private:
        std::shared_ptr<int> value_;
    };

public:
    TaskB(const std::shared_ptr<int>& value) : value_(value) {}

    int GetValue() const { return *value_; }

private:
    std::shared_ptr<int> value_;
};

TaskB printIntV4() {
    IntReaderB reader1;
    int total = co_await reader1;

    IntReaderB reader2;
    total += co_await reader2;

    IntReaderB reader3;
    total += co_await reader3;

    co_return total;  // 使用 co_return 返回值
}

// ========================= co_return ==================
class IntReaderC {
public:
    bool await_ready() { return false; }

    void await_suspend(std::coroutine_handle<> handle) {
        std::thread thread([this, handle]() {
            static int seed = 0;
            value_ = ++seed;

            handle.resume();
        });

        thread.detach();
    }

    int await_resume() { return value_; }

private:
    int value_{};
};

class TaskC {
public:
    class promise_type {
    public:
        TaskC get_return_object() {
            return TaskC{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always yield_value(int value) {
            value_ = value;
            return {};
        }

        void return_void() {}

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }

        void unhandled_exception() {}

        int GetValue() { return value_; }

    private:
        int value_;
    };

public:
    TaskC(std::coroutine_handle<promise_type> handle) : coroutine_handle_(handle) {}

    void Next() { return coroutine_handle_.resume(); }

    int GetValue() const { return coroutine_handle_.promise().GetValue(); }

private:
    std::coroutine_handle<promise_type> coroutine_handle_;
};

TaskC printIntV5() {
    int i = 0;
    while (true) {
        IntReaderC reader;
        printf("~第[%d]轮\n", i);
        int value = co_await reader;
        printf("--第[%d]轮\n", i);
        co_yield value;
        printf("---第[%d]轮\n", i);
        i++;
    }

    // co_return total;  // 使用 co_return 返回值
}

void runCoroutines() {
    // printIntV1();
    // printIntV2();
    // printIntV3();
    // printf("继续执行任务\n");
    // auto v4 = printIntV4();

    /*
      std::string line;
      while (std::cin >> line) {
          printf("v4[%d]\n", v4.GetValue());
      }
    */
    auto task = printIntV5();

    std::string line;
    while (std::cin >> line) {
        std::cout << task.GetValue() << std::endl;
        task.Next();
    }

    // 休眠一下
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // coro_v2();
}
