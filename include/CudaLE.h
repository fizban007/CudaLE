/////////////////////////////////////////////////////////////////////////////////////////
///
///           \file  CudaLE.h
///
/// __Description__:     Main include file for the CudaLE lib
///
/// __Version__:         1.0\n
/// __Author__:          Alex Chen, fizban007@gmail.com\n
/// __Organization__:    Columbia University
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef  _CUDALE_H_
#define  _CUDALE_H_

#include "cudaControl.h"
#include "Operators.h"
#include "Variable.h"
#include "Functions.h"
#include "Derivative.h"

#ifndef DEFINE_FUNCTOR
#define DEFINE_FUNCTOR(NAME, FUNCTOR)                    \
    private:                                             \
    typedef typeof(FUNCTOR) NAME ## _type;               \
    NAME ## _type defaultValue_ ## NAME () {             \
        return FUNCTOR;                                  \
    }                                                    \
public:                                                  \
NAME ## _type NAME                         
    
#endif

#endif   // ----- #ifndef _CUDALE_H_  ----- 
