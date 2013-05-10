#ifndef _GAMELOGINOBSERVER_H_
#define _GAMELOGINOBSERVER_H_

#include "CObserver.h"

class GameLoginObserver : public CObserver
{
public:
	GameLoginObserver(void);
	~GameLoginObserver(void);
	
	virtual void onResponseHandler( CResponse* reponse );
	virtual void registerReceiver( CActivity* activity );

};

#endif //_GAMELOGINOBSERVER_H_