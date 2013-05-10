#include "CApplication.h"
#include "CActivityService.h"
#include "CNotificationService.h"
#include "CDataCloudService.h"
#include "CNetService.h"
#include "CPlusInclude.h"
#include "CRDef.h"
#include "CCobraObjectPool.h"
#include "CService.h"
#include "CIntent.h"
#include "CActivity.h"
#include <stdlib.h>

#if 1
#include "CXmlUtils.h"
#endif


CApplication::CApplication( void )
	:m_CobraPool(NULL),
	m_bInit(false)
{
}

CApplication::~CApplication( void )
{
}


bool CApplication::isInit()
{
	return m_bInit;
}


void CApplication::onCreate()
{
	m_CobraPool = new CCobraObjectPool();
	loadCobraConfig("CobraMainConfig.xml");
}

/*
	loadCobraConfig 读取配置表
*/
void CApplication::loadCobraConfig(const char* xmlPath)
{
	if(xmlPath == NULL) return;
	pugi::xml_document doc;
	if(doc.load_file(xmlPath))
	{
	 	pugi::xml_node rootNode = doc.child("CobraConfig");		
		const char* versonCode = rootNode.child_value("versionCode");
		const char* versionName = rootNode.child_value("versionName");
		pugi::xml_node  serverNode = rootNode.child("Services");
		pugi::xml_node ddd = rootNode.child("versionCode");
		pugi::xml_node eleNode;
		std::string serverName;
		for (eleNode = serverNode.first_child();eleNode;eleNode= serverNode.next_sibling())
		{
			serverName = eleNode.attribute("name").as_string();
			if( serverName.compare(SERVICE_ACTIVITY))
			{
				CActivityService::getInstance()->onStart();
				CActivityService::getInstance()->setObjectID(SERVICE_ACTIVITY_GUID);
				m_CobraPool->addCobraObject(CActivityService::getInstance());
			}
			else if(serverName.compare(SERVICE_NOTIFICATION))
			{
				CNotificationService::getInstance()->onStart();
				CNotificationService::getInstance()->setObjectID(SERVICE_NOTIFICATION_GUID);
				m_CobraPool->addCobraObject(CNotificationService::getInstance());
			}
			else if( serverName.compare(SERVICE_DATACLOUD))
			{
				CDataCloudService::getInstance()->onStart();
				CDataCloudService::getInstance()->setObjectID(SERVICE_DATACLOUD_GUID);
				m_CobraPool->addCobraObject(CDataCloudService::getInstance());
			}
			else if(serverName.compare(SERVICE_NET))
			{
				CNetService::getInstance()->onStart();
				CNetService::getInstance()->setObjectID(SERVICE_NET_GUID);
				m_CobraPool->addCobraObject(CNetService::getInstance());
			}
		}
	}
}

/*
	读取应用服务对象
*/	
CService* CApplication::getServiceById( int id )
{
	return dynamic_cast<CService*>(m_CobraPool->getCobraObjectById(id));
}

void CApplication::onFinish()
{
	COBRA_SAFE_DELETE(m_CobraPool);
	CActivityService::getInstance()->onFinish();
	CNotificationService::getInstance()->onFinish();
	CDataCloudService::getInstance()->onFinish();
}

void CApplication::bindService( CIntent* intent )
{
	if( intent == NULL) return;
	if( intent->getServiceID() == -1 ) return;
	CActivity* activity = dynamic_cast<CActivity*>(CActivityService::getInstance()->getCobraObjectById(intent->getTargetKey()));
	CService* service = getServiceById(intent->getServiceID());
	if(service)
		service->addCobraObject(activity);
}

void CApplication::unBindService( CIntent* intent )
{
	if( intent == NULL) return;
	if( intent->getServiceID() == -1 ) return;
	CActivity* activity = dynamic_cast<CActivity*>(CActivityService::getInstance()->getCobraObjectById(intent->getTargetKey()));
	CService* service = getServiceById(intent->getServiceID());
	if(service)
		service->removeCobraObject(activity);
}

bool CApplication::isServiceRunnable( int serviceID )
{
	CService* service = getServiceById(serviceID);
	if(service)
		return service->isRunning();
	return false;
}
