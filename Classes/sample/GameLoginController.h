#ifndef _GAMELOGINCONTROLLER_H_
#define _GAMELOGINCONTROLLER_H_

#include "CObserver.h"
#include "RConfig.h"

class GameRegisterContoller : public CController
{
public:
	static std::string GAMEREGISTERCONTOLLER;
public:
	GameRegisterContoller(void);
	virtual ~GameRegisterContoller(void);
	virtual void execute(void* data);
};

#endif	//_GAMELOGINCONTROLLER_H_