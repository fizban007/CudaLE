#ifndef  _DERIVATIVE_H_
#define  _DERIVATIVE_H_


#include <math.h>
#include "cudaControl.h"
#include "Functions.h"

namespace CudaLE {

////////////////////////////////////////////////////////////////////////////////
///  Forward declaration
////////////////////////////////////////////////////////////////////////////////
template <int Argument, typename Expr>
struct Derivative;

template <int Argument, int Arg2, typename Expr>
typename Derivative<Argument, typename Derivative<Arg2, Expr>::result_type>::result_type 
D(const Derivative<Arg2, Expr>& deriv);

template <int Argument, typename Op, typename Left, typename Right>
typename Derivative<Argument, BinaryOp<Op, Left, Right> >::result_type
D(const BinaryOp<Op, Left, Right>& expr);

template <int Argument,typename Op, typename Right>
typename Derivative<Argument, BinaryOp<Op, double, Right> >::result_type
D(const BinaryOp<Op, double, Right>& expr);

template <int Argument,typename Op, typename Left>
typename Derivative<Argument, BinaryOp<Op, Left, double> >::result_type
D(const BinaryOp<Op, Left, double>& expr);

template <int Argument,typename Op, typename Expr>
typename Derivative<Argument, UnaryOp<Op, Expr> >::result_type
D(const UnaryOp<Op, Expr>& expr);

template <int Argument, int n>
typename Derivative<Argument, Var<n, double> >::result_type
D(const Var<n, double>& var);

template <int Argument>
typename Derivative<Argument, double>::result_type
D(const double& val);

////////////////////////////////////////////////////////////////////////////////
///  Template classes
////////////////////////////////////////////////////////////////////////////////
template <int Argument, int Arg2, typename Expr>
struct Derivative<Argument, Derivative<Arg2, Expr> >
{
    typedef typename Derivative<Arg2, Expr>::result_type arg_type;
    typedef typename Derivative<Argument, arg_type>::result_type result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(arg_type expr) : derivative(D<Argument>(expr)) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Left, typename Right>
struct Derivative<Argument, BinaryOp<Plus, Left, Right> >
{
    // Left left;
    // Right right;
    typedef BinaryOp<Plus, Left, Right> arg_type;
    typedef BinaryOp<Plus, typename Derivative<Argument, Left>::result_type
                     , typename Derivative<Argument, Right>::result_type > result_type;
    result_type derivative;
    
    // HOST_DEVICE Derivative(Left t1, Right t2) : left(t1), right(t2),  {}
    HOST_DEVICE Derivative(Left t1, Right t2) : derivative(D<Argument>(t1), D<Argument>(t2)) {}
    HOST_DEVICE Derivative(arg_type expr) : derivative(D<Argument>(expr.left), D<Argument>(expr.right)) {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Left, typename Right>
struct Derivative<Argument, BinaryOp<Minus, Left, Right> >
{
    // Left left;
    // Right right;
    typedef BinaryOp<Minus, Left, Right> arg_type;
    typedef BinaryOp<Minus, typename Derivative<Argument, Left>::result_type
                     , typename Derivative<Argument, Right>::result_type > result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Left t1, Right t2) : derivative(D<Argument>(t1), D<Argument>(t2))  {}
    HOST_DEVICE Derivative(arg_type expr) : derivative(D<Argument>(expr.left), D<Argument>(expr.right)) {}
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
    typedef BinaryOp<Multiply, Left, Right> arg_type;
    typedef BinaryOp<Plus, BinaryOp<Multiply, Left, typename Derivative<Argument, Right>::result_type >,
                     BinaryOp<Multiply, typename Derivative<Argument, Left>::result_type, Right> > result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Left t1, Right t2) : derivative(t1 * D<Argument>(t2), D<Argument>(t1) * t2) {}
    HOST_DEVICE Derivative(arg_type expr) : 
        derivative(expr.left * D<Argument>(expr.right), D<Argument>(expr.left) * expr.right) {}
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
    typedef BinaryOp<Divide, Left, Right> arg_type;
    typedef BinaryOp<Divide, BinaryOp<Minus,
                                      BinaryOp<Multiply, typename Derivative<Argument, Left>::resut_type, Right>,
                                      BinaryOp<Multiply, Left, typename Derivative<Argument, Right>::result_type> >,
                     BinaryOp<Multiply, Right, Right> > result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Left t1, Right t2) : 
        derivative(D<Argument>(t1) * t2 - t1 * D<Argument>(t2), t2 * t2) {}
    HOST_DEVICE Derivative(arg_type expr) : 
        derivative(D<Argument>(expr.left) * expr.right - expr.left * D<Argument>(expr.right), expr.right * expr.right) {}

    HOST_DEVICE Derivative() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Arg>
struct Derivative<Argument, UnaryOp<Sin, Arg> >
{
    typedef UnaryOp<Sin, Arg> arg_type;
    typedef BinaryOp<Multiply, UnaryOp<Cos, Arg>,
                     typename Derivative<Argument, Arg>::result_type > result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Arg arg) : derivative(cos(arg), D<Argument>(arg)) {}
    HOST_DEVICE Derivative(arg_type expr) : derivative(cos(expr.arg), D<Argument>(expr.arg)) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Arg>
struct Derivative<Argument, UnaryOp<Cos, Arg> >
{
    typedef UnaryOp<Sin, Arg> arg_type;
    typedef BinaryOp<Multiply, BinaryOp<Multiply, double, UnaryOp<Sin, Arg> >,
                     typename Derivative<Argument, Arg>::result_type > result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Arg arg) : derivative(-1.0 * sin(arg), D<Argument>(arg)) {}
    HOST_DEVICE Derivative(arg_type expr) : derivative(-1.0 * sin(expr.arg), D<Argument>(expr.arg)) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Arg>
struct Derivative<Argument, UnaryOp<Exp, Arg> >
{
    typedef UnaryOp<Exp, Arg> arg_type;
    typedef BinaryOp<Multiply, UnaryOp<Exp, Arg>,
                     typename Derivative<Argument, Arg>::result_type > result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Arg arg) : derivative(exp(arg), D<Argument>(arg)) {}
    HOST_DEVICE Derivative(arg_type expr) : derivative(exp(expr.arg), D<Argument>(expr.arg)) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Arg>
struct Derivative<Argument, UnaryOp<Log, Arg> >
{
    typedef UnaryOp<Log, Arg> arg_type;
    typedef BinaryOp<Divide, typename Derivative<Argument, Arg>::result_type, Arg> result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Arg arg) : derivative(D<Argument>(arg), arg) {}
    HOST_DEVICE Derivative(arg_type expr) : derivative(D<Argument>(expr.arg), expr.arg) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, int n, typename Arg>
struct Derivative<Argument, UnaryOp<Pow<n>, Arg> >
{
    typedef UnaryOp<Pow<n>, Arg> arg_type;
    typedef BinaryOp<Multiply, 
                     BinaryOp<Multiply, double, typename Derivative<Argument, Arg>::result_type>
                     , UnaryOp<Pow< n-1 >, Arg> > 
        result_type;
    result_type derivative;
    
    HOST_DEVICE Derivative(Arg arg) : derivative((double)n * D<Argument>(arg), pow<n-1>(arg)) {}
    HOST_DEVICE Derivative(arg_type expr) : derivative((double)n * D<Argument>(expr.arg), pow<n-1>(expr.arg)) {}
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument>
struct Derivative<Argument, ConstOp>
{
    typedef ConstOp arg_type;
    typedef double result_type;
    result_type derivative;

    HOST_DEVICE Derivative() : derivative(0.0) {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative;
    }
};

template <int Argument>
struct Derivative<Argument, double>
{
    typedef double arg_type;
    typedef double result_type;
    result_type derivative;

    HOST_DEVICE Derivative() : derivative(0.0) {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative;
    }
};

template <int Argument, int var>
struct Derivative<Argument, Var<var, double > >
{
    typedef Var<var, double> arg_type;
    typedef ConstOp result_type;
    result_type derivative;

    HOST_DEVICE Derivative() {
        if (Argument == var)
            derivative = ConstOp(1.0);
        else
            derivative = ConstOp(0.0);
    }
    
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return derivative(x1, x2, x3);
    }
};

template <int Argument, typename Op, typename Left, typename Right>
typename Derivative<Argument, BinaryOp<Op, Left, Right> >::result_type 
D(const BinaryOp<Op, Left, Right>& expr) {
    return Derivative<Argument, BinaryOp<Op, Left, Right> >(expr.left, expr.right).derivative;
}

template <int Argument,typename Op, typename Right>
typename Derivative<Argument, BinaryOp<Op, double, Right> >::result_type 
D(const BinaryOp<Op, double, Right>& expr) {
    return Derivative<Argument, BinaryOp<Op, double, Right> >(expr.left.val, expr.right).derivative;
}

template <int Argument,typename Op, typename Left>
typename Derivative<Argument, BinaryOp<Op, Left, double> >::result_type 
D(const BinaryOp<Op, Left, double>& expr) {
    return Derivative<Argument, BinaryOp<Op, Left, double> >(expr.left, expr.right.val).derivative;
}

template <int Argument,typename Op, typename Expr>
typename Derivative<Argument, UnaryOp<Op, Expr> >::result_type
D(const UnaryOp<Op, Expr>& expr) {
    return Derivative<Argument, UnaryOp<Op, Expr> >(expr.arg).derivative;
}

template <int Argument, int n>
typename Derivative<Argument, Var<n, double> >::result_type
D(const Var<n, double>& var) {
    return Derivative<Argument, Var<n, double> >().derivative;
}

template <int Argument>
typename Derivative<Argument, double>::result_type
D(const double& val) {
    return Derivative<Argument, double>().derivative;
}

template <int Argument>
typename Derivative<Argument, ConstOp>::result_type
D(const ConstOp& val) {
    return Derivative<Argument, ConstOp>().derivative;
}

template <int Argument, int Arg2, typename Expr>
typename Derivative<Argument, typename Derivative<Arg2, Expr>::result_type>::result_type
D(const Derivative<Arg2, Expr>& deriv) {
    return D<Argument>(deriv.derivative);
}


}

#endif   // ----- #ifndef _DERIVATIVE_H_  ----- 
