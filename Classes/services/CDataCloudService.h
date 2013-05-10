#ifndef _CDATACLOUDSERVICE_H_
#define _CDATACLOUDSERVICE_H_

#include "CService.h"
#include "CSingleton.h"
#include <map>

class CCobraObjectPool;

class CDataCloudService : public CService,public CSingleton<CDataCloudService>
{
public:
	virtual void onStart();
	virtual void onAcceptIntent( CIntent* intent);
	virtual void onSynchResponse( CResponse* response );
	virtual void onFinish();
private:
	friend class CSingleton<CDataCloudService>;
	CDataCloudService(void);
	~CDataCloudService(void);
private:
	std::map<int,CCobraObjectPool*> m_dataCloudPool;
};

#endif //_CDATACLOUDSERVICE_H_