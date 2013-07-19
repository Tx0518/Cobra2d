#ifndef _CBASETYPES_H_
#define _CBASETYPES_H_

#include <limits.h>
#include <stddef.h>

typedef signed char			sChar;
typedef signed char			int8;
typedef signed short		int16;

typedef unsigned char		uInt8;
typedef unsigned short		uInt16;

#ifndef _INT32
#define _INT32
typedef int					int32;
#endif

#ifndef _UINT32
#define _UINT32
typedef unsigned int		uInt32;
#endif

#if __LP64__
typedef long				int64;
#else
typedef long long			int64;
#endif


#if __LP64__
typedef unsigned long		uInt64;
#else
typedef unsigned long long	uInt64;
#endif

const uInt8  kuint8max  = (( uInt8) 0xFF);
const uInt16 kuint16max = ((uInt16) 0xFFFF);
const uInt32 kuint32max = ((uInt32) 0xFFFFFFFF);
const  int8  kint8min   = ((  int8) 0x80);
const  int8  kint8max   = ((  int8) 0x7F);
const  int16 kint16min  = (( int16) 0x8000);
const  int16 kint16max  = (( int16) 0x7FFF);
const  int32 kint32min  = (( int32) 0x80000000);
const  int32 kint32max  = (( int32) 0x7FFFFFFF);

#endif	//_CBASETYPES_H_