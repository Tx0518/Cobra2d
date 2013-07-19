#include "CApplication.h"
#include "CActivityService.h"
#include "CNotificationService.h"
#include "CDataCloudService.h"
#include "CEventService.h"
#include "CGUIService.h"
#include "CNetService.h"
#include "CHttpService.h"
#include "CService.h"
#include "CIntent.h"
#include "CActivity.h"
#include "CMemoryCache.h"
#include "CSTLHelper.h"


CApplication* CApplication::m_Instance = NULL;

CApplication::CApplication( void )
	:m_bIsCreated(false)
{
}

CApplication::~CApplication( void )
{
}

CApplication* CApplication::shareApplication()
{
	if(m_Instance == NULL)
		m_Instance = new CApplication();
	return  m_Instance;
}

void CApplication::onCreate()
{
	if(m_bIsCreated) return;
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CActivityService());
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CNetService());
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CNotificationService());
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CDataCloudService());
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CGuiService());
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CHttpService());
	MemoryCacheShare->putExtra(COBRA_SERVICES,new CEventService());
	m_bIsCreated = true;
}

void CApplication::onFinish()
{
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_ACTIVITY);
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_NET);
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_NOTIFICATION);
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_GUI);
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_DATACLOUD);
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_HTTP);
	MemoryCacheShare->deleteExtra(COBRA_SERVICES,SERVICE_EVENT);
}

void CApplication::didEnterApplication()
{
// 	CCobraObjectPool* servicePool = MemoryCacheShare->getCobraObjectPool(COBRA_SERVICES);
// 	COBRA_CHECK_NULL(servicePool);
// 	servicePool->getObjectPool();
}

void CApplication::didExitApplication()
{

}

void CApplication::onMainLoop()
{
	//do something
}
