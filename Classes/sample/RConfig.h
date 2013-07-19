#ifndef _RCONFIG_H_
#define _RCONFIG_H_

/************************************************************************/
/* 
	RConfig
	TODO:统一应用对象GUID
*/
/************************************************************************/
class RConfig
{
	//Activty
public:
	static const int R_GAMEACTIVITY = 0x0001;

	static const int  R_LOGIN_ACTIVITY = 0x1000;

	//Observer
public:
	static const int  R_GAMELOGIN_OBSERVER = 0x2000;
};

#endif //_RCONFIG_H_