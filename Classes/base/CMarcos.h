#ifndef _CMARCOS_H_
#define _CMARCOS_H_

#include <assert.h>
#include <stdlib.h>

#define COBRA_RENDEENQINE_UNKNOWN				0
#define COBRA_RENDEENQINE_COCOS2DX				1
#define COBRA_RENDEENQINE_IRRLICHT				2


#define COBRA_PLATFORM_UNKNOWN					0
#define COBRA_PLATFORM_IOS						1
#define COBRA_PLATFORM_ANDROID					2
#define COBRA_PLATFORM_WIN32					3
#define COBRA_PLATFORM_MARMALADE				4
#define COBRA_PLATFORM_LINUX					5
#define COBRA_PLATFORM_BADA						6
#define COBRA_PLATFORM_BLACKBERRY				7
#define COBRA_PLATFORM_MAC						8
#define COBRA_PLATFORM_NACL						9

#define COBRA_TARGET_RENDEENQINE             COBRA_RENDEENQINE_COCOS2DX

#define COBRA_TARGET_PLATFORM				 COBRA_PLATFORM_UNKNOWN

//win32
#if defined(WIN32) && defined(_WINDOWS)
#undef COBRA_TARGET_PLATFORM	
#define COBRA_TARGET_PLATFORM				COBRA_PLATFORM_WIN32
#endif

//android
#if defined(ANDROID)
#undef COBRA_TARGET_PLATFORM	
#define COBRA_TARGET_PLATFORM				COBRA_PLATFORM_ANDROID
#endif

//iphone
#if defined(IPHONE)
#undef COBRA_TARGET_PLATFORM	
#define COBRA_TARGET_PLATFORM				COBRA_PLATFORM_IOS
#endif


#define COBRA_CREATE_PROPERTY(varType,varName,funName)\
protected:varType varName;\
public: virtual varType get##funName(void) {return varName;}\
public: virtual void set##funName(varType var) {varName = var;}

//////////////////////////////////////////////////////////////////////////
//未实现函数定义
#define COBRA_CREATE_PROPERTY_UNIMPLEMENT(varType,varName,funName)\
protected:varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);


//////////////////////////////////////////////////////////////////////////
//未实现函数定义
#define COBRA_CREATE_PROPERTY_BY_BOOL_UNIMPLEMENT(varType,varName,funName)\
protected:bool varName;\
public: virtual bool is##funName(void);\
public: virtual void set##funName(bool var);

#define COBRA_CREATE_PROPERTY_BY_BOOL(varName,funName)\
protected:bool varName;\
public: virtual bool is##funName(void) {return varName;}\
public: virtual void set##funName(bool var) {varName = var;}

#define COBRA_CREATE_PROPERTY_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) {return varName;}\
public: virtual void set##funName(const varType& var) {varName = var;}

#define COBRA_CREATE_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define COBRA_CREATE_PROPERTY_READONLY_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }


#define COBRA_SAFE_DELETE(p)						do{if(p){delete p;p = 0;}}while(0)
#define COBRA_SAFE_DELETE_ARRAY(p)					do{if(p){delete[] p;p = 0;}}while(0)
#define COBRA_BREAK_IF(cond)						if(cond) break
#define COBRA_RETURN_IF(cond)						if(cond) return;
#define COBRA_UNASSIGNED(p)						    if( p == -1) return
#define COBRA_CHECK_NULL(instance)					if(instance == 0) return
#define COBRA_CHECK_UNKNOWN(p)						if(p == COBRA_UNKNOWN) return

#if defined(_USRDLL)
#define CC_DLL     __declspec(dllexport)
#else         /* use a DLL library */
#define CC_DLL     __declspec(dllimport)
#endif


#define COBRA_ASSERT(cond,msg)    assert(cond)

/* Define NULL pointer value */
#ifndef NULL
#define NULL    0
#endif



/* Define default value of all int*/
#ifndef COBRA_UNKNOWN
#define COBRA_UNKNOWN		-99999
#endif

/* Define String default value */

#ifndef COBRA_STRING_DEFAULT_VALULE
#define COBRA_STRING_DEFAULT_VALULE		""
#endif


#define coabs(a)  ((a) > 0 ? (a):(-(a)))
#define comax(a,b) (((a)>(b))?(a):(b))
#define comin(a,b) (((a)>(b))?(b):(a))

#include "cocos2d.h"
#define LOG		cocos2d::CCLog
#define  ENTERFUNC()    LOG("enter func %s in %s",__FUNCTION__, __FILE__)
#define  LVFUNC()       LOG("leave func %s in %s",__FUNCTION__, __FILE__)

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

//platform
//////////////////////////////////////////////////////////////////////////
//#define  ANDROID
//#define  IOS
//////////////////////////////////////////////////////////////////////////
#endif