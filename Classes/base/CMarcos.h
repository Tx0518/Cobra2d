#ifndef _CMARCOS_H_
#define _CMARCOS_H_

#include <assert.h>

#define COBRA_RENDEENQINE_UNKNOWN				0
#define COBRA_RENDEENQINE_COCOS2DX				1
#define COBRA_RENDEENQINE_IRRLICHT					2

#define COBRA_TARGET_RENDEENQINE             COBRA_RENDEENQINE_COCOS2DX

#define COBRA_CREATE_PROPERTY(varType,varName,funName)\
protected:varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);

#define COBRA_CREATE_PROPERTY_BY_BOOL(varName,funName)\
protected:bool varName;\
public: virtual bool is##funName(void);\
public: virtual void set##funName(bool var);

#define COBRA_CREATE_PROPERTY_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void);\
public: virtual void set##funName(const varType& var);

#define COBRA_CREATE_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define COBRA_CREATE_PROPERTY_READONLY_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }


#define COBRA_SAFE_DELETE(p)							do{if(p){delete p;p = 0;}}while(0)
#define COBRA_SAFE_DELETE_ARRAY(p)				do{if(p){delete[] p;p = 0;}}while(0)
#define COBRA_BREAK_IF(cond)							if(cond) break
#define COBRA_UNASSIGNED(p)						    if( p == -1) return

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

#include "cocos2d.h"
#define LOG		cocos2d::CCLog
#define  ENTERFUNC()    LOG("enter func %s in %s",__FUNCTION__, __FILE__)
#define  LVFUNC()       LOG("leave func %s in %s",__FUNCTION__, __FILE__)


//platform
//////////////////////////////////////////////////////////////////////////
//#define  ANDROID
//#define  IOS
//////////////////////////////////////////////////////////////////////////
#endif