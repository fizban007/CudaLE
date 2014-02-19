#include <math.h>
#include "cudaDef.h"
#include "Operators.h"

namespace CudaLE {

struct Sin
{
    HOST_DEVICE static double apply(double x) {
        return sin(x);
    }
};

template <typename Arg>
UnaryOp<Sin, Arg> _sin(Arg arg) {
    return UnaryOp<Sin, Arg>(arg);
}

struct Cos
{
    HOST_DEVICE static double apply(double x) {
        return cos(x);
    }
};

template <typename Arg>
UnaryOp<Cos, Arg> _cos(Arg arg) {
    return UnaryOp<Cos, Arg>(arg);
}

struct Exp
{
    HOST_DEVICE static double apply(double x) {
        return exp(x);
    }
};

template <typename Arg>
UnaryOp<Exp, Arg> _exp(Arg arg) {
    return UnaryOp<Exp, Arg>(arg);
}

struct Log
{
    HOST_DEVICE static double apply(double x) {
        return log(x);
    }
};

template <typename Arg>
UnaryOp<Log, Arg> _log(Arg arg) {
    return UnaryOp<Log, Arg>(arg);
}

struct Plus
{
    HOST_DEVICE static double apply(double a, double b) {
        return a + b;
    }
};

template <typename Left, typename Right>
BinaryOp<Plus, Left, Right> operator+ (Left lhs, Right rhs) {
    return BinaryOp<Plus, Left, Right>(lhs, rhs);
}

struct Minus
{
    HOST_DEVICE static double apply(double a, double b) {
        return a - b;
    }
};

template <typename Left, typename Right>
BinaryOp<Minus, Left, Right> operator- (Left lhs, Right rhs) {
    return BinaryOp<Minus, Left, Right>(lhs, rhs);
}

struct Multiply
{
    HOST_DEVICE static double apply(double a, double b) {
        return a * b;
    }
};

template <typename Left, typename Right>
BinaryOp<Multiply, Left, Right> operator* (Left lhs, Right rhs) {
    return BinaryOp<Multiply, Left, Right>(lhs, rhs);
}

struct Divide
{
    HOST_DEVICE static double apply(double a, double b) {
        return a / b;
    }
};

template <typename Left, typename Right>
BinaryOp<Divide, Left, Right> operator/ (Left lhs, Right rhs) {
    return BinaryOp<Divide, Left, Right>(lhs, rhs);
}

template<int power>
struct Pow
{
    HOST_DEVICE static double apply(double a) {
        return pow(a, power);
    }
};

template <int power, typename Arg>
UnaryOp<Pow<power>, Arg> _pow(Arg arg) {
    return UnaryOp<Pow<power>, Arg>(arg);
}

}
