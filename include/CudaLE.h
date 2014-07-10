/////////////////////////////////////////////////////////////////////////////////////////
///
///           \file  CudaLE.h
///
/// __Description__:     Main include file for the CudaLE lib
///
/// __Last modified__:   <2014-07-10 12:58:27 alex>\n
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
  #define DEFINE_FUNCTOR(NAME, FUNCTOR)                  \
      typedef typeof(FUNCTOR) type_ ## NAME;             \
      type_ ## NAME NAME
#endif

#endif   // ----- #ifndef _CUDALE_H_  ----- 
