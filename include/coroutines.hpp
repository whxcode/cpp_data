#pragma once
#include <chrono>
#include <cmath>
#include <coroutine>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

// 定义一个简单的生成器类
struct Generator {
    struct promise_type {
        int value;

        // 协程启动时返回的对象
        Generator get_return_object() {
            return Generator(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        // 协程暂停时
        std::suspend_always yield_value(int v) {
            value = v;
            return {};
        }

        // 协程开始和结束时的行为
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() {
        if (handle) handle.destroy();
    }

    bool next() {
        if (handle.done()) return false;  // 检查协程是否完成
        handle.resume();                  // 恢复协程
        return true;
    }

    int current_value() const {
        return handle.promise().value;  // 获取当前值
    }
};

void runCoroutines();
