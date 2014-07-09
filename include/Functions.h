#ifndef  _FUNCTIONS_H_
#define  _FUNCTIONS_H_

#include <math.h>
#include "cudaControl.h"
#include "Operators.h"

namespace CudaLE {

struct Sin
{
    HD_INLINE static double apply(double x) {
        return sin(x);
    }
};

template <typename Arg>
UnaryOp<Sin, Arg> sin(Arg arg) {
    return UnaryOp<Sin, Arg>(arg);
}

struct Cos
{
    HD_INLINE static double apply(double x) {
        return cos(x);
    }
};

template <typename Arg>
UnaryOp<Cos, Arg> cos(Arg arg) {
    return UnaryOp<Cos, Arg>(arg);
}

struct Exp
{
    HD_INLINE static double apply(double x) {
        return exp(x);
    }
};

template <typename Arg>
UnaryOp<Exp, Arg> exp(Arg arg) {
    return UnaryOp<Exp, Arg>(arg);
}

struct Log
{
    HD_INLINE static double apply(double x) {
        return log(x);
    }
};

template <typename Arg>
UnaryOp<Log, Arg> log(Arg arg) {
    return UnaryOp<Log, Arg>(arg);
}

struct Plus
{
    HD_INLINE static double apply(double a, double b) {
        return a + b;
    }
};

template <typename Left, typename Right>
BinaryOp<Plus, Left, Right> operator+ (Left lhs, Right rhs) {
    return BinaryOp<Plus, Left, Right>(lhs, rhs);
}

// template <typename Left>
// BinaryOp<Plus, Left, ConstOp> operator+ (Left lhs, double rhs) {
//     return BinaryOp<Plus, Left, ConstOp>(lhs, ConstOp(rhs));
// }

// template <typename Right>
// BinaryOp<Plus, ConstOp, Right> operator+ (double lhs, Right rhs) {
//     return BinaryOp<Plus, ConstOp, Right>(ConstOp(lhs), rhs);
// }

struct Minus
{
    HD_INLINE static double apply(double a, double b) {
        return a - b;
    }
};

template <typename Left, typename Right>
BinaryOp<Minus, Left, Right> operator- (Left lhs, Right rhs) {
    return BinaryOp<Minus, Left, Right>(lhs, rhs);
}

struct Multiply
{
    HD_INLINE static double apply(double a, double b) {
        return a * b;
    }
};

template <typename Left, typename Right>
BinaryOp<Multiply, Left, Right> operator* (Left lhs, Right rhs) {
    return BinaryOp<Multiply, Left, Right>(lhs, rhs);
}

// template <typename Left>
// BinaryOp<Multiply, Left, ConstOp> operator* (Left lhs, double rhs) {
//     return BinaryOp<Multiply, Left, ConstOp>(lhs, ConstOp(rhs));
// }

// template <typename Right>
// BinaryOp<Multiply, ConstOp, Right> operator* (double lhs, Right rhs) {
//     return BinaryOp<Multiply, ConstOp, Right>(ConstOp(lhs), rhs);
// }

struct Divide
{
    HD_INLINE static double apply(double a, double b) {
        return a / b;
    }
};

template <typename Left, typename Right>
BinaryOp<Divide, Left, Right> operator/ (Left lhs, Right rhs) {
    return BinaryOp<Divide, Left, Right>(lhs, rhs);
}

// template <typename Left>
// BinaryOp<Divide, Left, ConstOp> operator/ (Left lhs, double rhs) {
//     return BinaryOp<Divide, Left, ConstOp>(lhs, ConstOp(rhs));
// }

// template <typename Right>
// BinaryOp<Divide, ConstOp, Right> operator/ (double lhs, Right rhs) {
//     return BinaryOp<Divide, ConstOp, Right>(ConstOp(lhs), rhs);
// }

template<int power>
struct Pow
{
    HD_INLINE static double apply(double a) {
        return pow(a, power);
    }
};

template <int power, typename Arg>
UnaryOp<Pow<power>, Arg> pow(Arg arg) {
    return UnaryOp<Pow<power>, Arg>(arg);
}

}



#endif   // ----- #ifndef _FUNCTIONS_H_  ----- 
