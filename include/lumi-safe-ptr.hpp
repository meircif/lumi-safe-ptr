#ifndef LUMI_SAFE_PTR_H_INCLUDED_
#define LUMI_SAFE_PTR_H_INCLUDED_

#include <memory>
#include <type_traits>

namespace lumi {


template<class T> class ToClass {};

template<class... T> class ToClasses: public ToClass<T>... {
public:
    static constexpr bool cycle_check(void) { return true; }
};

template<class F> class CycleCheckFromClass {};

template<class F, class T>
constexpr void cycle_assert(F const *, T const * const &) {
    static_assert(
        std::is_base_of_v<ToClass<F>,
        CycleCheckFromClass<T> >,
        "cycle check for strong pointer missing from ‘LUMI_CYCLE_CHECK’ macro");
}

template<class, class> class CycleCheck;

template<class T> class CycleCheck<T, T> {
public:
    static constexpr bool check(void) { return false; }
};

template<class F, class T, int = sizeof(CycleCheck<F, T>)>
constexpr bool cycle_check(int) { return CycleCheck<F, T>::check(); }

template<class, class>
constexpr bool cycle_check(char) { return true; }

template<class F, class... T>
constexpr bool cycle_check(void) {
    return (true && ... && cycle_check<F, T>(1));
}


#ifdef NO_CYCLE_CHECK

#define LUMI_STRONG_PTR(to) std::shared_ptr<to>
#define LUMI_CYCLE_CHECK(from, to...)

#else

#define LUMI_STRONG_PTR(to) \
constexpr void lumi_cycle_check(to* t) { lumi::cycle_assert(t, this); } \
std::shared_ptr<to> 
#define LUMI_CYCLE_CHECK(from, to...) \
template<> \
class lumi::CycleCheckFromClass<from>: public lumi::ToClasses<to> {}; \
static_assert(lumi::cycle_check<from, to>(), \
    "cyclic reference detected in type ‘" #from "’"); \
template<class F> class lumi::CycleCheck<F, from> { \
public: \
    static constexpr bool check(void) { \
        return lumi::cycle_check<F, to>(); \
    } \
};

#endif


} // namespace lumi

#endif  // LUMI_SAFE_PTR_H_INCLUDED_
