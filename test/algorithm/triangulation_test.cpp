#include "CMTL/algorithm/triangulation.h"

#include <iostream>

void test1() {}

struct A {
  int a;
};

struct B : public A {
  B(A aa) : A(aa) {}
  int b;
};

int main() {
  A AA = {10};
  B BB(AA);
  std::cout << BB.a << std::endl;
  test1();
}