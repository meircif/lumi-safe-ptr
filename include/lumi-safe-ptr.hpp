#ifndef LUMI_SAFE_PTR_H_INCLUDED_
#define LUMI_SAFE_PTR_H_INCLUDED_


#include <memory>
#include <type_traits>


template<class T> constexpr bool cycle_check(void) { return true; }

template<class... T> constexpr bool cycle_check_all(void) {
    return (true && ... && cycle_check<T>());
}

template<class T> class ToClass {};

template<class... T> class ToClasses: public ToClass<T>... {};

template<class F> class CycleCheckFromClass {};

template<class F, class T>
constexpr void cycle_assert(F const *, T const * const &) {
    static_assert(
        std::is_base_of_v<ToClass<F>,
        CycleCheckFromClass<T> >,
        "cycle check missing");
}


#ifdef NO_CC
#define LUMI_STRONG_PTR(to) std::shared_ptr<to>
#define LUMI_CYCLE_CHECK(from, to...)
#else
#define LUMI_STRONG_PTR(to) \
constexpr void lumi_cycle_check(to* t) { cycle_assert(t, this); } \
std::shared_ptr<to> 
#define LUMI_CYCLE_CHECK(from, to...) \
template<> class CycleCheckFromClass<from>: public ToClasses<to> {}; \
template<> constexpr bool cycle_check<from>(void) \
  { return cycle_check_all<to>(); } \
static_assert(cycle_check<from>());
#endif


#endif  /*LUMI_SAFE_PTR_H_INCLUDED_*/
