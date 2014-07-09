#ifndef  _DERIVATIVE_H_
#define  _DERIVATIVE_H_


#include <math.h>
#include "cudaControl.h"
#include "Functions.h"

namespace CudaLE {

template <int Argument, typename Expr>
struct Derivative
{
    Expr expr;
    typedef Derivative<Argument, Expr> type;
    
    HOST_DEVICE Derivative(Expr ex) : expr(ex) {}
    HOST_DEVICE Derivative() {}

    // HOST_DEVICE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
    // }
};

template <int Argument, typename Left, typename Right>
struct Derivative<Argument, BinaryOp<Plus, Left, Right> >
{
    // Left left;
    // Right right;
    BinaryOp<Plus, Derivative<Argument, Left>, Derivative<Argument, Right> > derivative;
    
    // HOST_DEVICE Derivative(Left t1, Right t2) : left(t1), right(t2),  {}
    HOST_DEVICE Derivative() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Left, typename Right>
struct Derivative<Argument, BinaryOp<Minus, Left, Right> >
{
    // Left left;
    // Right right;
    BinaryOp<Minus, Derivative<Argument, Left>, Derivative<Argument, Right> > derivative;
    
    // HOST_DEVICE Derivative(Left t1, Right t2) : left(t1), right(t2),  {}
    HOST_DEVICE Derivative() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Left, typename Right>
struct Derivative<Argument, BinaryOp<Multiply, Left, Right> >
{
    // Left left;
    // Right right;
    BinaryOp<Plus, BinaryOp<Multiply, Left, Derivative<Argument, Right> >,
             BinaryOp<Multiply, Derivative<Argument, Left>, Right> > derivative;
    
    // HOST_DEVICE Derivative(Left t1, Right t2) : left(t1), right(t2),  {}
    HOST_DEVICE Derivative() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};


template <int Argument, typename Left, typename Right>
struct Derivative<Argument, BinaryOp<Divide, Left, Right> >
{
    // Left left;
    // Right right;
    BinaryOp<Divide, BinaryOp<Minus,
                              BinaryOp<Multiply, Derivative<Argument, Left>, Right>,
                              BinaryOp<Multiply, Left, Derivative<Argument, Right> > >,
             BinaryOp<Multiply, Right, Right> > derivative;
    
    // HOST_DEVICE Derivative(Left t1, Right t2) : left(t1), right(t2),  {}
    HOST_DEVICE Derivative() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Arg>
struct Derivative<Argument, UnaryOp<Sin, Arg> >
{
    BinaryOp<Multiply, UnaryOp<Cos, Arg>,
             Derivative<Argument, Arg> > derivative;
    
    HOST_DEVICE Derivative() {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Arg>
struct Derivative<Argument, UnaryOp<Cos, Arg> >
{
    BinaryOp<Multiply, BinaryOp<Multiply, ConstOp, UnaryOp<Sin, Arg> >,
             Derivative<Argument, Arg> > derivative;
    
    HOST_DEVICE Derivative() : derivative(-sin(Arg()) * D(Arg())) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument>
struct Derivative<Argument, double>
{
    HOST_DEVICE Derivative() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return 0.0;
    }
};

template <int Argument, int var>
struct Derivative<Argument, Var<var, double > >
{
    HOST_DEVICE Derivative() {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        if (Argument == var)
            return 1.0;
        else
            return 0.0;
    }
};

template <int Argument, typename Expr>
Derivative<Argument, Expr> D(Expr expr) {
    return Derivative<Argument, Expr>(expr);
}

}

#endif   // ----- #ifndef _DERIVATIVE_H_  ----- 