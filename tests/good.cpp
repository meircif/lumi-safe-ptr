#include "lumi-safe-ptr.hpp"

#include <iostream>

class A;
namespace bbb {class B;}
namespace ccc {class C;}


class A {
public:
    LUMI_STRONG_PTR(bbb::B) b;
    LUMI_STRONG_PTR(ccc::C) c;
};

#ifdef MAKE_MISSING_CHECK
LUMI_CYCLE_CHECK(A, bbb::B)
#else
LUMI_CYCLE_CHECK(A, bbb::B, ccc::C)
#endif


namespace bbb { 
class B {
public:
    LUMI_STRONG_PTR(ccc::C) c;
}; }

LUMI_CYCLE_CHECK(bbb::B, ccc::C)


namespace ccc { class C {
public:
#ifdef MAKE_CYCLE_ERROR
    LUMI_STRONG_PTR(A) a;
#else
    std::weak_ptr<A> a;
#endif
}; }

#ifdef MAKE_CYCLE_ERROR
LUMI_CYCLE_CHECK(ccc::C, A)
#endif


int main(void) {
    auto a = std::make_shared<A>();
    a->b = std::make_shared<bbb::B>();
    a->b->c = std::make_shared<ccc::C>();
    a->b->c->a = a;
    std::cout << "Done" << std::endl;
    a = nullptr;
    return 0;
}
