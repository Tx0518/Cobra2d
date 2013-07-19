#ifndef _CDATACLOUDSERVICE_H_
#define _CDATACLOUDSERVICE_H_

#include "CService.h"
#include <map>

class CCobraObjectPool;

class CDataCloudService : public CService
{
public:
	CDataCloudService(void);
	virtual ~CDataCloudService(void);
	virtual void onStart();
	virtual void onAcceptIntent( CIntent* intent);
	virtual void onSynchResponse( CResponse* response );
	virtual void onFinish();
private:
	std::map<int,CCobraObjectPool*> m_dataCloudPool;
};

#endif //_CDATACLOUDSERVICE_H_