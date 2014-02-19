/////////////////////////////////////////////////////////////////////////////////////////
///
///           \file  Operators.h
///
/// __Description__:     Declares the base operators for the expression template
///
/// __Last modified__:   <2014-02-19 13:23:43 alex>\n
/// __Version__:         1.0\n
/// __Author__:          Alex Chen, fizban007@gmail.com\n
/// __Organization__:    Columbia University
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef  _OPERATORS_H_
#define  _OPERATORS_H_

#include "cudaDef.h"

namespace CudaET {

template <typename Op, typename Left, typename Right>
struct BinaryOp
{
    Left left;
    Right right;
    HOST_DEVICE BinaryOp(Left t1, Right t2) : left(t1), right(t2) {}

    HOST_DEVICE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return Op::apply(left(x1, x2, x3), right(x1, x2, x3));
    }
};

template <typename Op, typename Arg>
struct UnaryOp
{
    Arg arg;
    HOST_DEVICE UnaryOp(Arg t1) : arg(t1) {}

    HOST_DEVICE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return Op::apply(arg(x1, x2, x3));
    }
};

}

#endif   // ----- #ifndef _OPERATORS_H_  ----- 
