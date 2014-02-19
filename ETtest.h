#include <math.h>

#ifdef __CUDACC__
#define HOST_DEVICE __host__ __device__
#else
#define HOST_DEVICE
#endif

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

struct Sin
{
    HOST_DEVICE static double apply(double x) {
        return sin(x);
    }
};

struct Cos
{
    HOST_DEVICE static double apply(double x) {
        return cos(x);
    }
};

struct Exp
{
    HOST_DEVICE static double apply(double x) {
        return exp(x);
    }
};

struct Log
{
    HOST_DEVICE static double apply(double x) {
        return log(x);
    }
};

struct Plus
{
    HOST_DEVICE static double apply(double a, double b) {
        return a + b;
    }
};

struct Minus
{
    HOST_DEVICE static double apply(double a, double b) {
        return a - b;
    }
};

struct Multiply
{
    HOST_DEVICE static double apply(double a, double b) {
        return a * b;
    }
};

struct Divide
{
    HOST_DEVICE static double apply(double a, double b) {
        return a / b;
    }
};

template <typename Left, typename Right>
BinaryOp<Plus, Left, Right> operator+ (Left lhs, Right rhs) {
    return BinaryOp<Plus, Left, Right>(lhs, rhs);
}

template <typename Left, typename Right>
BinaryOp<Minus, Left, Right> operator- (Left lhs, Right rhs) {
    return BinaryOp<Minus, Left, Right>(lhs, rhs);
}

template <typename Left, typename Right>
BinaryOp<Multiply, Left, Right> operator* (Left lhs, Right rhs) {
    return BinaryOp<Multiply, Left, Right>(lhs, rhs);
}

template <typename Left, typename Right>
BinaryOp<Divide, Left, Right> operator/ (Left lhs, Right rhs) {
    return BinaryOp<Divide, Left, Right>(lhs, rhs);
}

template <typename Arg>
UnaryOp<Sin, Arg> _sin(Arg arg) {
    return UnaryOp<Sin, Arg>(arg);
}

template <typename Arg>
UnaryOp<Cos, Arg> _cos(Arg arg) {
    return UnaryOp<Cos, Arg>(arg);
}

template <typename Arg>
UnaryOp<Exp, Arg> _exp(Arg arg) {
    return UnaryOp<Exp, Arg>(arg);
}

template <typename Arg>
UnaryOp<Log, Arg> _log(Arg arg) {
    return UnaryOp<Log, Arg>(arg);
}

Var<1, double> _1;
Var<2, double> _2;
Var<3, double> _3;
