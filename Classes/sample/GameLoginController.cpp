#include "GameLoginController.h"
#include "CMemoryCache.h"
#include "RConfig.h"
#include "CActivity.h"

std::string GameRegisterContoller::GAMEREGISTERCONTOLLER = "GameRegisterContoller";

GameRegisterContoller::GameRegisterContoller()
{
	setObserverID(RConfig::R_GAMELOGIN_OBSERVER);
}

GameRegisterContoller::~GameRegisterContoller()
{
}

void GameRegisterContoller::execute( void* data )
{
	CActivity* activity = dynamic_cast<CActivity*>(MemoryCacheShare->getExtra(COBRA_ACTIVITY,RConfig::R_GAMEACTIVITY));
	COBRA_CHECK_NULL(activity);
	//activity->getGUI();
}
