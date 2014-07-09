/////////////////////////////////////////////////////////////////////////////////////////
///
///           \file  Operators.h
///
/// __Description__:     Declares the base operators for the expression template
///
/// __Last modified__:   <2014-07-09 01:46:36 alex>\n
/// __Version__:         1.0\n
/// __Author__:          Alex Chen, fizban007@gmail.com\n
/// __Organization__:    Columbia University
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef  _OPERATORS_H_
#define  _OPERATORS_H_

#include "cudaControl.h"

namespace CudaLE {

struct ConstOp
{
    double val;
    HOST_DEVICE ConstOp(double v) : val(v) {}
    HOST_DEVICE ConstOp(const ConstOp& op) : val(op.val) {}
    HOST_DEVICE ConstOp() : val(0.0) {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return val;
    }
};

template <typename Op, typename Left, typename Right>
struct BinaryOp
{
    Left left;
    Right right;
    typedef BinaryOp<Op, Left, Right> type;

    HOST_DEVICE BinaryOp(Left t1, Right t2) : left(t1), right(t2) {}
    HOST_DEVICE BinaryOp(const type& op) : left(op.left), right(op.right) {}
    HOST_DEVICE BinaryOp() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return Op::apply(left(x1, x2, x3), right(x1, x2, x3));
    }
};

template <typename Op, typename Left>
struct BinaryOp<Op, Left, double>
{
    Left left;
    ConstOp right;
    typedef BinaryOp<Op, Left, double> type;

    HOST_DEVICE BinaryOp(Left t1, double t2) : left(t1), right(ConstOp(t2)) {}
    HOST_DEVICE BinaryOp(const type& op) : left(op.left), right(op.right) {}
    HOST_DEVICE BinaryOp() {}
        
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return Op::apply(left(x1, x2, x3), right(x1, x2, x3));
    }
};

template <typename Op, typename Right>
struct BinaryOp<Op, double, Right>
{
    ConstOp left;
    Right right;
    typedef BinaryOp<Op, double, Right> type;

    HOST_DEVICE BinaryOp(double t1, Right t2) : left(ConstOp(t1)), right(t2) {}
    HOST_DEVICE BinaryOp(const type& op) : left(op.left), right(op.right) {}
    HOST_DEVICE BinaryOp() {}
        
    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return Op::apply(left(x1, x2, x3), right(x1, x2, x3));
    }
};

// template <typename Op, typename Left, typename Right>
// struct BinaryOp<Op, Left*, Right>
// {
//     Left* left;
//     Right right;
//     typedef BinaryOp<Op, Left*, Right> type;

//     HOST_DEVICE BinaryOp(Left* t1, Right t2) : left(t1), right(t2) {}
//     HOST_DEVICE BinaryOp() {}
        
//     HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
//         return Op::apply((*left)(x1, x2, x3), right(x1, x2, x3));
//     }
// };

// template <typename Op, typename Left, typename Right>
// struct BinaryOp<Op, Left, Right*>
// {
//     Left left;
//     Right* right;
//     typedef BinaryOp<Op, Left, Right*> type;

//     HOST_DEVICE BinaryOp(Left t1, Right* t2) : left(t1), right(t2) {}
//     HOST_DEVICE BinaryOp() {}
    
//     HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
//         return Op::apply(left(x1, x2, x3), (*right)(x1, x2, x3));
//     }
// };

// template <typename Op, typename Left, typename Right>
// struct BinaryOp<Op, Left*, Right*>
// {
//     Left* left;
//     Right* right;
//     typedef BinaryOp<Op, Left*, Right*> type;

//     HOST_DEVICE BinaryOp(Left* t1, Right* t2) : left(t1), right(t2) {}
//     HOST_DEVICE BinaryOp() {}
        
//     HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
//         return Op::apply((*left)(x1, x2, x3), (*right)(x1, x2, x3));
//     }
// };

template <typename Op, typename Arg>
struct UnaryOp
{
    Arg arg;
    typedef UnaryOp<Op, Arg> type;

    HOST_DEVICE UnaryOp(Arg t1) : arg(t1) {}
    HOST_DEVICE UnaryOp(const type& op) : arg(op.arg) {}
    HOST_DEVICE UnaryOp() {}

    HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
        return Op::apply(arg(x1, x2, x3));
    }
};

// template <typename Op, typename Arg>
// struct UnaryOp<Op, Arg*>
// {
//     Arg* arg;
//     typedef UnaryOp<Op, Arg*> type;

//     HOST_DEVICE UnaryOp(Arg* t1) : arg(t1) {}
//     HOST_DEVICE UnaryOp() {}

//     HD_INLINE double operator() (double x1, double x2 = 0.0, double x3 = 0.0) {
//         return Op::apply((*arg)(x1, x2, x3));
//     }
// };
    
}

#endif   // ----- #ifndef _OPERATORS_H_  ----- 

