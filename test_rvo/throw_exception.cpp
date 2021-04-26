#include <iostream>

struct C {
  C() = default;
  C(const C&) { std::cout << "Hello World!\n"; }
};

void f() {
  C c;
  throw c;  // copying the named object c into the exception object.
}  // It is unclear whether this copy may be elided (omitted).

int main() {
  try {
    f();
  } catch (C c) {  // copying the exception object into the temporary in the
                   // exception declaration.
  }  // It is also unclear whether this copy may be elided (omitted).
}