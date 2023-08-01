[![CI Status](https://github.com/meircif/lumi-safe-ptr/workflows/CI/badge.svg)](https://github.com/meircif/lumi-safe-ptr/actions)

# lumi-safe-ptr - Safe C++ Smart Pointers Wrapper

The "Lumi" project goal is to provide tools for writing safe and efficient code.
This `lumi-safe-ptr` library provides C++ smart pointers wrappers that makes them even more safe to use.

While C++ smart pointers help a lot in writing memory safe code - they still have some pitfalls and problems that users can mistakenly fall into. These are the issues that `lumi-safe-ptr` library solves:

- [lumi-safe-ptr - Safe C++ Smart Pointers Wrapper](#lumi-safe-ptr---safe-c-smart-pointers-wrapper)
  - [Avoid shared\_ptr circular references](#avoid-shared_ptr-circular-references)
  - [Future Work](#future-work)

## Avoid shared_ptr circular references

This is the most known `shared_ptr` issue that is now avoidable 😃.

It can be solved using macros `LUMI_CYCLE_CHECK` and `LUMI_STRONG_PTR` that will raise a compilation error when a circular reference is detected. Their usage is simple:

1. Every `shared_ptr` member in a type should be declared using `LUMI_STRONG_PTR(type) name;` (instead of `std::shared_ptr<type> name;`).
2. Before Every type that uses `LUMI_STRONG_PTR` add (in the global scope) `LUMI_CYCLE_CHECK(type, pointed_types...)`

For example:
```
#include "lumi-safe-ptr.hpp"

LUMI_CYCLE_CHECK(module::A, module::B, module::C)

namespace module {

class A {
    LUMI_STRONG_PTR(B) b;
    LUMI_STRONG_PTR(C) c;
};

}
```

## Future Work

More Issues that may be solved next as long as they can be technically done using C++ syntax:

1. Access moved `unique_ptr`
2. Using unchecked `weak_ptr`
3. Deleting the raw pointers
4. Thread safety
5. Using non-heap pointers
6. Not using `make_shared`
7. Safe arrays of pointers
8. Derived to base class pointer
9. Garbage collecting pointer
