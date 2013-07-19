#ifndef _GAMEAPPLICATION_H_
#define _GAMEAPPLICATION_H_

#include "CApplication.h"

class GameActivity;

class GameApplication : public CApplication
{
public:
	GameApplication(void);
	~GameApplication(void);
	virtual void onCreate();
	virtual void onFinish();
	virtual void onMainLoop();
	virtual void didEnterApplication();
	virtual void didExitApplication();
protected:
	GameActivity* mainActivity;
};

#endif //_GAMEAPPLICATION_H_