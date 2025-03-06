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
