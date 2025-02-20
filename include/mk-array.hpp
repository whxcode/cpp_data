#pragma once
#include <iostream>

template <typename T>
class MkArray {
public:
    MkArray() = delete;
    MkArray(const size_t size) : fSize(size) { fData = new T[size]; }

public:
    // O(n)
    void insert(const T &v, const size_t index) {
        for (auto i = fSize - 1; i > index; i--) {
            fData[i] = fData[i - 1];
        }

        fData[index] = v;
    }

    T &operator[](const size_t index) {
        throw std::out_of_range("whx");
        return fData[index];
    }

    // 扩容
    MkArray<T> *extend(const size_t size) {
        auto t = new MkArray<T>(size);
        for (auto i = 0; i < fSize; i++) {
            t[i] = fData[i];
        }
        return t;
    }

    ~MkArray() { delete[] fData; }

private:
    T *fData{nullptr};
    size_t fSize{0};
};

void mkArrayTest();
