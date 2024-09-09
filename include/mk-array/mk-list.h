

#pragma
#include <functional>
#include <iostream>

template <typename T> class MkList {
public:
  struct Node {
    T *fValue{nullptr};
    Node *fNext{nullptr};
  };

public:
  MkList() { fHead = new Node(); }
  ~MkList() {
    Node *temp = fHead->fNext;

    for (int i = 0; i < fSize; ++i) {
      Node *cur = temp;
      temp = temp->fNext;
      free(cur->fValue);
      free(cur);
    }

    free(fHead);
  }

public:
  void push(const T &value) {
    Node *temp = fSize == 0 ? fHead : fTail;

    Node *node = new Node();
    node->fValue = new T(value);
    node->fNext = fHead;
    temp->fNext = node;

    fTail = node;

    fSize++;
  }

  void insert(const T &value, size_t index) {
    if (index < 0 || index > fSize) {
      return;
    }

    if (index == fSize) {
      push(value);
      return;
    }

    Node *temp = fHead;
    for (int i = 0; i < index; ++i) {
      temp = temp->fNext;
    }

    Node *node = new Node();
    node->fValue = new T(value);

    node->fNext = temp->fNext;
    temp->fNext = node;

    fSize++;
  }

  void detach(size_t index) {
    if (index < 0 || index > fSize || fSize == 0) {
      return;
    }
    Node *temp = fHead;

    for (int i = 0; i < index; ++i) {
      temp = temp->fNext;
    }

    Node *cur = temp->fNext;
    temp->fNext = cur->fNext;
    fSize--;

    if (cur == fTail) {
      fTail = cur->fNext;
    }

    free(cur->fValue);
    free(cur);
  }

  void foreach (std::function<void(T)> func) {
    Node *temp = fHead->fNext;
    for (int i = 0; i < fSize; ++i) {
      func(*temp->fValue);
      temp = temp->fNext;
    }
  }

  size_t getSize() { return fSize; }

private:
  Node *fHead{nullptr};
  Node *fTail{nullptr};
  size_t fSize{0};
};

void MkArrayList();
