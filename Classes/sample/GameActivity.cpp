#include "GameActivity.h"
#include "CGui.h"
#include "CResponse.h"

#include "RConfig.h"
#include "GameLoginController.h"

GameActivity::GameActivity()
{
}

GameActivity::~GameActivity()
{
}

void GameActivity::onCreate()
{
	m_pGui = new CGui(100,50);
	setObserverId(RConfig::R_GAMELOGIN_OBSERVER);
//	addController(GameRegisterContoller::GAMEREGISTERCONTOLLER);
}

void GameActivity::onFinish()
{
	CActivity::onFinish();
}

void GameActivity::onResponseHandler( CResponse* response )
{
}
