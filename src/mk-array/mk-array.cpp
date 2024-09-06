#include "../../include/mk-array/mk-array.h"

void MkArrayTest() {
  size_t SIZE = 10;
  MkArray<int> dogs(SIZE);

  for (int i = 0; i < SIZE; ++i) {
    dogs[i] = i * 100;
  }

  dogs(2) = -1;
  dogs(0) = -50;

  for (int i = 0; i < SIZE; ++i) {
    printf("%d\n", dogs[i]);
  }

  auto t = dogs.map<double>([](int v) -> double { return v * 0.5; });
  t->foreach ([](double v) { printf("%f\n", v); });

  std::cout << "tt:" << t->at(-1) << std::endl;
}
