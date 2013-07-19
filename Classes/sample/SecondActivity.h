#ifndef _SECONDACTIVITY_H_
#define _SECONDACTIVITY_H_

#include "CActivity.h"

class SecondActivity : public CActivity
{
public:
	SecondActivity(void);
	virtual ~SecondActivity(void);

	virtual void onCreate();
	virtual void onFinish();
	virtual void onResponseHandler( CResponse* response );
	virtual void onUpdate( void* pMsgHead );
};

#endif  //_SECONDACTIVITY_H_