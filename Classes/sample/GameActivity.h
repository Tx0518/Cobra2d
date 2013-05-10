#ifndef _GAMEACTIVITY_H_
#define _GAMEACTIVITY_H_

#include "CActivity.h"
#include "CSingleton.h"

class GameActivity : public CActivity,public CSingleton<GameActivity>
{
public:
	virtual void onCreate();
	virtual void onFinish();
private:
	GameActivity(void);
	~GameActivity(void);
	friend class CSingleton<GameActivity>;
};

#endif //_GAMEACTIVITY_H_