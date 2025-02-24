#pragma once
#include <functional>
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
        // throw std::out_of_range("whx");
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

class MkList {
public:
    struct Node {
        int *fValue{nullptr};
        Node *fNext{nullptr};
    };

public:
    void insert(const int &v) {
        auto node = new Node;
        node->fValue = new int(v);
        node->fNext = fHead;

        if (fTail == nullptr) {
            fHead->fNext = node;
            fTail = node;
            fTail->fNext = fHead->fNext;
            ++fSize;
            return;
        }

        auto temp = fHead->fNext;

        node->fNext = temp;
        fHead->fNext = node;
        fTail->fNext = fHead->fNext;

        ++fSize;
    }

    void each() {
        std::function<void(Node * start, Node * end)> p = [&p](Node *start, Node *end) {
            if (start == end) {
                printf("%d\n", *start->fValue);
                return;
            }

            p(start->fNext, end);
            printf("%d\n", *start->fValue);
        };

        p(fHead->fNext, fTail);
    }

protected:
    Node *fHead{new Node};
    Node *fTail{nullptr};
    size_t fSize;
};

class MkStack : public MkList {
public:
    void push(const int v) { this->insert(v); }
    int pop() {
        auto top = fHead->fNext;
        fHead->fNext = top->fNext;
        fTail->fNext = fHead->fNext;

        --fSize;
        auto v = *top->fValue;
        delete top->fValue;
        delete top;
        return v;
    }

    bool empty() { return fSize == 0; }
};

void mkArrayTest();
