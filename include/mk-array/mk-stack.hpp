#pragma once
#include "./mk-list.hpp"

template <typename T>
class MkStack {
public:
    MkStack() { fList = new MkList<T>(); }
    ~MkStack() { delete fList; }

public:
    void push(const T &value) { fList->push(value); }
    void pop() { fList->detach(fList->getSize() - 1); }
    const T &top() const { return *fList->at(fList->getSize() - 1)->fValue; }
    size_t getSize() const { return fList->getSize(); }
    bool isEmpty() const { return fList->getSize() == 0; }

private:
    MkList<T> *fList;
};

void MkStackTest();
