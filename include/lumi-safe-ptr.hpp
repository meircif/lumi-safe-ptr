#ifndef LUMI_SAFE_PTR_H_INCLUDED_
#define LUMI_SAFE_PTR_H_INCLUDED_

#include <memory>
#include <type_traits>

namespace lumi {


template<class, class> class CycleCheck;

template<class T> class CycleCheck<T, T> {
public:
    static constexpr bool check(void) { return false; }
};

template<class From, class To, int = sizeof(CycleCheck<From, To>)>
constexpr bool cycle_check(int) { return CycleCheck<From, To>::check(); }

template<class, class>
constexpr bool cycle_check(char) { return true; }

template<class From, class... Tos>
constexpr bool cycle_check(void) {
    return (true && ... && cycle_check<From, Tos>(1));
}


template<class>
class CycleCheckExists {};

template<class... Tos>
class CycleChecksExists: public CycleCheckExists<Tos>... {};

template<class From, class To>
constexpr void cycle_check_exists(From const * const &, To const *) {
    static_assert(
        std::is_base_of_v<CycleCheckExists<To>, CycleCheck<To, From> >,
        "cycle check for strong pointer missing from ‘LUMI_CYCLE_CHECK’ macro");
}


#ifdef NO_CYCLE_CHECK

#define LUMI_STRONG_PTR(to) std::shared_ptr<to>
#define LUMI_CYCLE_CHECK(from, to...)

#else

#define LUMI_STRONG_PTR(To) \
constexpr void lumi_cycle_check(To* t) { lumi::cycle_check_exists(this, t); } \
std::shared_ptr<To> 

#define LUMI_CYCLE_CHECK(From, Tos...) \
static_assert(lumi::cycle_check<From, Tos>(), \
    "cyclic reference detected in type ‘" #From "’"); \
template<class Other> \
class lumi::CycleCheck<Other, From>: lumi::CycleChecksExists<Tos> { \
public: \
    static constexpr bool check(void) { return lumi::cycle_check<Other, Tos>(); } \
};

#endif


} // namespace lumi

#endif  // LUMI_SAFE_PTR_H_INCLUDED_
