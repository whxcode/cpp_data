#pragma once
#include <cstring>
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

class MkLinkedStack {
public:
    struct Node {
        int fValue;
        Node *fNext{nullptr};
    };

public:
    void push(const int v) {
        auto node = new Node;
        node->fValue = v;

        if (fTop == nullptr) {
            fTop = node;
        } else {
            node->fNext = fTop;
            fTop = node;
        }

        ++fSize;
    }

    bool isEmpty() { return fSize == 0; }

    int pop() {
        if (isEmpty()) {
            return -1;
        }

        auto top = fTop;
        int value = top->fValue;
        fTop = top->fNext;
        delete top;
        --fSize;
        return value;
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }

        return fTop->fValue;
    }

private:
    size_t fSize{0};
    Node *fTop{nullptr};
};

class ArrayQueue {
private:
    int *fData{nullptr};
    size_t fFront{0};
    size_t fQueSize{0};
    size_t fQueCapacity{0};

public:
    ArrayQueue(const size_t queCapacity) : fQueCapacity(queCapacity) {
        fData = new int[queCapacity];
        // 当前指针指向的位置为头.
        fFront = fQueSize = 0;
    };

    ~ArrayQueue() { delete[] fData; }
    size_t capacity() const { return fQueCapacity; }
    size_t size() const { return fQueSize; }
    size_t isEmpty() const { return size() == 0; }

    void push(const int v) {
        if (fQueSize == fQueCapacity) {
            fQueCapacity *= 2;
            auto temp = fData;
            fData = new int[fQueCapacity];
            memcpy(fData, temp, sizeof(int) * fQueSize);

            // std::cout << "满了" << std::endl;
            // return;
        }

        size_t rear = (fFront + fQueSize) % fQueCapacity;
        fData[rear] = v;
        ++fQueSize;
    }

    int peek() {
        if (!isEmpty()) return fData[fFront];

        return -1;
    }

    int pop() {
        int num = peek();
        fFront = (fFront + 1) % fQueCapacity;
        --fQueSize;

        return num;
    }
};

class MkDbLink {
public:
    struct Node {
        int fValue{-1};
        Node *fNext{nullptr};
        Node *fPrev{nullptr};
    };

public:
    void push(const int value) {
        Node *node = new Node;
        node->fValue = value;

        if (fHead == nullptr) {
            fHead = node;
            fTail = node;
        } else {
            node->fPrev = fTail;
            fTail->fNext = node;
            fTail = node;
        }

        ++fSize;
    }

    void unShift(const int value) {
        Node *node = new Node;
        node->fValue = value;
        if (fHead == nullptr) {
            fHead = node;
            fTail = node;
        } else {
            node->fNext = fHead;
            fHead->fPrev = node;
            fHead = node;
        }

        ++fSize;
    }

    int pop() {
        if (this->empty()) {
            return 0;
        }

        auto tail = fTail;
        int value = tail->fValue;

        fTail = tail->fPrev;

        if (fTail) {
            fTail->fNext = nullptr;
        }

        --fSize;

        delete tail;
        return value;
    }

    int shift() {
        if (empty()) {
            return 0;
        }

        auto head = fHead;
        int value = head->fValue;

        fHead = head->fNext;
        if (fHead) {
            fHead->fPrev = nullptr;
        }

        --fSize;
        delete head;
        return value;
    }

    bool empty() const { return fSize == 0; }

private:
    Node *fHead{nullptr};
    Node *fTail{nullptr};
    size_t fSize{0};
};

void mkArrayTest();
