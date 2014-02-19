#include<iostream>
#include<math.h>
#include "CudaLE.h"

using namespace CudaLE;

const CoordinateType type = COORD_CYLINDRICAL;

// typedef UnaryOp<Id, double> Var;

int main () 
{
    // Var _x(1), _y(2);
    auto myF = MakeFunc(_sin(_1) + _2);
    // std::cout << sin(2.0) + 3.0 << std::endl;
    // std::cout << (_log(_1) * _exp(_2) + _3)(2.0, -1, 1.0) << std::endl;
    std::cout << _sin(_pow<2>(_1) + _2)(2.0, 3.0) << std::endl;
    std::cout << myF.getFunc()(1.0, 2.0) << std::endl;
    return 0;
}
