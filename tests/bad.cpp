#include "lumi-safe-ptr.hpp"

#include <iostream>

class A;
namespace bbb {class B;}
namespace ccc {class C;}


LUMI_CYCLE_CHECK(ccc::C, A)
LUMI_CYCLE_CHECK(bbb::B, ccc::C)
LUMI_CYCLE_CHECK(A, bbb::B, ccc::C)


class A {
public:
    LUMI_STRONG_PTR(bbb::B) b;
    LUMI_STRONG_PTR(ccc::C) c;
};

namespace bbb { class B {
public:
    LUMI_STRONG_PTR(ccc::C) c;
}; }

namespace ccc { class C {
public:
    LUMI_STRONG_PTR(A) a;
    // std::weak_ptr<A> a;
}; }


int main(void) {
    auto a = std::make_shared<A>();
    a->b = std::make_shared<bbb::B>();
    a->b->c = std::make_shared<ccc::C>();
    a->b->c->a = a;
    std::cout << "Done" << std::endl;
    a = nullptr;
    return 0;
}
