#include "GameApplication.h"
#include "GameActivity.h"
#include "RConfig.h"
#include "CIntent.h"
#include "CHandler.h"

GameApplication::GameApplication( void )
	:mainActivity(NULL)
{
}

GameApplication::~GameApplication( void )
{
}

void GameApplication::onCreate()
{
	CApplication::onCreate();
	mainActivity = new GameActivity();
	CIntent intent(INTENT_START_ACTIVITY,RConfig::R_GAMEACTIVITY,SERVICE_ACTIVITY,mainActivity);
	CHandler::onHandler(&intent);
}

void GameApplication::onFinish()
{
	CApplication::onFinish();
	mainActivity->onFinish();
	COBRA_SAFE_DELETE(mainActivity);
}

void GameApplication::didEnterApplication()
{
	CApplication::didEnterApplication();
}

void GameApplication::didExitApplication()
{
	CApplication::didExitApplication();
}

void GameApplication::onMainLoop()
{
	
}
