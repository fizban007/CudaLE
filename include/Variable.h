/////////////////////////////////////////////////////////////////////////////////////////
///
///           \file  Variable.h
///
/// __Description__:     Declares the variables used for the expression template
///
/// __Last modified__:   <2014-02-19 13:33:10 alex>\n
/// __Version__:         1.0\n
/// __Author__:          Alex Chen, fizban007@gmail.com\n
/// __Organization__:    Columbia University
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef  _VARIABLE_H_
#define  _VARIABLE_H_

#include "cudaDef.h"

namespace CudaET {

template <int Argument, typename Data>
struct Var
{
    HOST_DEVICE Data operator() (Data x1, Data x2 = 0.0, Data x3 = 0.0) {
        if (1 == Argument)
            return x1;
        else if (2 == Argument)
            return x2;
        else if (3 == Argument)
            return x3;
        else
            return Data();
    }
};

Var<1, double> _1;
Var<2, double> _2;
Var<3, double> _3;
}

#endif   // ----- #ifndef _VARIABLE_H_  ----- 