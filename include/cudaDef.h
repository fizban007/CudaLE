#ifndef  _CUDADEF_H_
#define  _CUDADEF_H_

#ifdef __CUDACC__
#define HOST_DEVICE __host__ __device__
#else
#define HOST_DEVICE
#endif

#endif   // ----- #ifndef _CUDADEF_H_  ----- 
