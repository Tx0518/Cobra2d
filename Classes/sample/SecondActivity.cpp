#include "SecondActivity.h"
#include "CGui.h"

SecondActivity::SecondActivity( void )
{
}

SecondActivity::~SecondActivity( void )
{
}

void SecondActivity::onCreate()
{
	CActivity::onCreate();
	this->m_pGui = new CGui(100,50);
}

void SecondActivity::onFinish()
{
	CActivity::onFinish();
}

void SecondActivity::onResponseHandler( CResponse* response )
{

}

void SecondActivity::onUpdate( void* pMsgHead )
{

}
