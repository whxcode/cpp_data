
#pragma
#include <functional>
#include <iostream>

template <typename T> class MkArray {
public:
  MkArray(size_t size) : fSize(size) { fArray = new T[size]; }

  ~MkArray() { delete fArray; }

public:
  void insert(size_t index, const T &v) {
    for (size_t i = fSize - 1; i > index; --i) {
      fArray[i] = fArray[i - 1];
    }

    fArray[index] = v;
  }

  void erase(size_t index) {
    for (size_t i = index; i < fSize - 1; ++i) {
      fArray[i] = fArray[i + 1];
    }
  }

  template <typename U> MkArray<U> *map(std::function<U(T)> f) {
    MkArray<U> *newArray = new MkArray<U>(fSize);

    for (size_t i = 0; i < fSize; ++i) {
      // newArray->at(i) = f(at(i));
      (*newArray)(i) = f((*this)(i));
    }

    return newArray;
  }

  void foreach (std::function<void(T)> f) {
    for (size_t i = 0; i < fSize; ++i) {
      f(fArray[i]);
    }
  }

  T &at(int index) {
    if (index < 0) {
      return fArray[fSize + index];
    }

    return fArray[index];
  }

public:
  T &operator[](size_t t) { return *(fArray + t); }
  T &operator()(size_t t) { return *(fArray + t); }
  T &operator()(size_t t, const T &value) { return *(fArray + t); }

private:
  T *fArray;
  size_t fSize;
};

void MkArrayTest();
