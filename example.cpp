#include <iostream>
#include <math.h>
#include "CudaLE.h"

using namespace CudaLE;

// #define MY_DECLARE_FUNCTOR_TYPE(a, b) typedef typeof(a) b
#define DEFINE_FUNCTOR(NAME, FUNCTOR)      \
    typedef typeof(FUNCTOR) type_ ## NAME; \
    type_ ## NAME NAME;               \

class FuncTest
{
public:
    DEFINE_FUNCTOR(f, sin(3.0 * _1) + 3.0 * _2);
    DEFINE_FUNCTOR(g, log(_1 * _2));

    FuncTest() : f(sin(3.0 * _1) + 3.0 * _2), 
                 g(log(_1 * _2)) {}
    virtual ~FuncTest() {}
}; // ----- end of class FuncTest -----


int main()
{
    FuncTest F;
    // typeof (_1) func;
    // typedef typeof(_1 + _2) functype;
    // functype func = _1 + _2;
    // std::cout << func(2.0, 3.0) << std::endl;
    std::cout << F.f(2.0, 3.0) << std::endl;
    std::cout << (2.0 * F.f * F.g)(2.0, 3.0) << std::endl;
    std::cout << (D<2>(F.f))(2.0, 3.0) << " " << 3.0 * cos(6.0) << " " << 3.0 << std::endl;
    // std::cout << (ConstOp(3.0) * f.get_f ())(2.0, 3.0) << std::endl;
    // std::cout << func(2.0, 3.0) << std::endl;
    // std::cout << f.get_functor2()(2.0, 3.0) << std::endl;
    return 0;
}










