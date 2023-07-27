# lumi-safe-ptr - Safe C++ Smart Pointers Wrapper

> **Warning**  
> This repo is in **WIP** state

The "Lumi" project goal is to provide tools for writing safe and efficient code.
This `lumi-safe-ptr` library provides C++ smart pointers wrappers that makes them even more safe to use.

While C++ smart pointers help a lot in writing memory safe code - they still have some pitfalls and problems that users can mistakenly fall into. These are the issues that `lumi-safe-ptr` library solves:

1. The infamous `shared_ptr` circular reference issue

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
