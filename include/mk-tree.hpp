#pragma once
#include <concepts>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>

void testTree();

template <typename T, typename Compare = std::less<T>>
class MkPileUp {
public:
    /* 构造方法，根据输入列表建堆 */
    void from(const std::vector<int> &nums) {
        fData = nums;

        for (int i = getParentIndex(fData.size() - 1); i >= 0; i--) {
            this->shiftDown(i);
        }
    }

public:
    size_t getLeftIndex(const size_t i) { return i * 2 + 1; }
    size_t getRightIndex(const size_t i) { return i * 2 + 2; }
    int getParentIndex(const size_t i) { return i == 0 ? -1 : int((i - 1) / 2); }

    const T &top() { return fData.front(); }

    void push(const T &v) {
        fData.push_back(v);
        shiftUp(fData.size() - 1);
    }

    bool empty() { return fData.empty(); }

    void pop() {
        if (fData.size() == 0) {
            return;
        }

        swap(0, fData.size() - 1);
        fData.pop_back();
        shiftDown(0);
    }

private:
    void swap(const size_t i, const size_t j) {
        auto temp = fData[i];
        fData[i] = fData[j];
        fData[j] = temp;
    }

    void shiftUp(const size_t i) {
        size_t index = i;

        while (true) {
            const auto p = getParentIndex(index);

            if (p < 0 || !fComp(fData[index], fData[p])) {
                break;
            }

            swap(index, p);
            index = p;
        }
    }

    void shiftDown(const size_t i) {
        size_t index = i;

        while (true) {
            auto leftIndex = getLeftIndex(index);
            auto rightIndex = getRightIndex(index);
            auto minIndex = index;

            if (leftIndex < fData.size() && fComp(fData[leftIndex], fData[minIndex])) {
                minIndex = leftIndex;
            }
            if (rightIndex < fData.size() && fComp(fData[rightIndex], fData[minIndex])) {
                minIndex = rightIndex;
            }

            if (minIndex == index) {
                break;
            }

            swap(index, minIndex);
            index = minIndex;
        }
    }

private:
    std::vector<T> fData;
    Compare fComp;  // 比较器，用于决定是大顶堆还是小顶堆
};

class MkArrayTree {
public:
    size_t size() { return fData.size(); }
    size_t leftIndex(const size_t i) { return i * 2 + 1; }
    size_t rightIndex(const size_t i) { return i * 2 + 2; }
    size_t parentIndex(const size_t i) { return i == 0 ? 0 : int((i - 1) / 2); }

    void push(const int v) { fData.push_back(v); }
    void dfs(const size_t i) {
        if (i >= fData.size()) {
            return;
        }
        dfs(leftIndex(i));
        printf("%d ", fData[i]);
        dfs(rightIndex(i));
    }

private:
    std::vector<int> fData;
};

class MkHeap {
public:
    int parentIndex(const size_t i) { return i == 0 ? 0 : int((i - 1) / 2); }
    int leftIndex(const size_t i) { return i * 2 + 1; }
    int rightIndex(const size_t i) { return i * 2 + 2; }

    void push(const int v) {
        fData.push_back(v);
        shiftUp(fData.size() - 1);
    }
    void pop() {
        // swap
        std::swap(fData[0], fData.back());
        fData.pop_back();
        shiftDown(0);
    }

    bool empty() { return fData.empty(); }

    int peek() { return fData[0]; }

private:
    void shiftUp(const int index) {
        auto i = index;

        while (true) {
            int p = parentIndex(i);
            if (p < 0 || fData[i] <= fData[p]) {
                break;
            }

            std::swap(fData[i], fData[p]);
            i = p;
        }
    }

    void shiftDown(const int index) {
        auto i = index;

        while (true) {
            auto l = leftIndex(i), r = rightIndex(i), max = i;
            if (l < fData.size() && fData[l] > fData[max]) {
                max = l;
            }

            if (r < fData.size() && fData[r] > fData[max]) {
                max = r;
            }
            if (max == i) {
                break;
            }

            std::swap(fData[i], fData[max]);
        }
    }

private:
    std::vector<int> fData;
};
