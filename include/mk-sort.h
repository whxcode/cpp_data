#pragma once
#include <vector>

class Heap {
public:
    static Heap Make(const std::vector<int> &data) {
        Heap h;
        h.fData = data;

        for (int i = h.getParentIndex(h.fData.size() - 1); i >= 0; i--) {
            h.shiftDown(i);
        }

        return h;
    }

public:
    int getParentIndex(int i) const { return (i - 1) / 2; }
    int getLeftIndex(int i) const { return 2 * i + 1; }
    int getRightIndex(int i) const { return 2 * i + 2; }

    void push(int val) {
        fData.push_back(val);
        shiftUp(fData.size() - 1);
    }

    int pop() {
        std::swap(fData[0], fData.back());
        int val = fData.back();
        fData.pop_back();
        shiftDown(0);
        return val;
    }

    bool empty() { return fData.empty(); }

    std::vector<int> toVector() {
        std::vector<int> data;

        while (!this->empty()) {
            data.push_back(this->pop());
        }

        return data;
    }

private:
    void shiftUp(const int index) {
        int i = index;
        while (true) {
            int parent = getParentIndex(i);

            if (parent < 0 || fData[i] <= fData[parent]) {
                break;
            }

            std::swap(fData[parent], fData[i]);
            i = parent;
        }
    }

    void shiftDown(const int index) {
        int i = index;

        // 找到最大值.
        while (true) {
            int left = getLeftIndex(i);
            int right = getRightIndex(i);
            int m = i;

            if (left < fData.size() && fData[m] <= fData[left]) {
                m = left;
            }

            if (right < fData.size() && fData[m] <= fData[right]) {
                m = right;
            }

            if (m == i) {
                break;
            }

            std::swap(fData[m], fData[i]);
            i = m;
        }
    }

private:
    std::vector<int> fData;
};

void testSort();
