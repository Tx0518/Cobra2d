#ifndef _GAMEROUTER_H_
#define _GAMEROUTER_H_

#include "CMsgSubject.h"

class GameRouter : public IMsgObserver
{
public:
	GameRouter(void);
	~GameRouter(void);

	virtual void onUpdate( void* pMsgHead );

protected:
private:
};

#endif	//_GAMEROUTER_H_