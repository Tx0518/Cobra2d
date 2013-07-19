#ifndef _GAMEACTIVITY_H_
#define _GAMEACTIVITY_H_

#include "CActivity.h"

class GameActivity : public CActivity
{
public:
	GameActivity(void);
	virtual ~GameActivity(void);
	virtual void onCreate();
	virtual void onFinish();
	virtual void onResponseHandler(CResponse* response);
};

#endif //_GAMEACTIVITY_H_