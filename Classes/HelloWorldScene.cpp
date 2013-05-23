#include "HelloWorldScene.h"
#include "CApplication.h"
#include <map>
#include "CPanel.h"
#include "CPushButton.h"
#include "CSorllPanel.h"
#include "CGraphic.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

HelloWorld::~HelloWorld()
{
	//remove it 
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->removeDelegate(m_pGUI);
	//release
	m_pGUI->release();
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
		
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
		//init GUI system
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		m_pGUI = new CGui(size.width,size.height);
		m_pGUI->setRect(CreateCRect(0,0,size.width,size.height));
		m_pGUI->setBkColor(CreateCColor(255,0,0,255));
		//add panel to gui
#if 0
		CPanel* pPanel = new CPanel();
		pPanel->setBkColor(CreateCColor(0,255,0,255));
		pPanel->setRect(CreateCRect(100,100,100,50));
		
		pPanel->setZOrder(0);
		m_pGUI->add(pPanel);

		//add panel2 to panel1
		CPanel* pPanel2 = new CPanel();
		pPanel2->setBkColor(CreateCColor(0,0,255,128));
		pPanel2->setRect(CreateCRect(0,25,100,10));
		pPanel->add(pPanel2);
		//set scale to parent all child will be effected!!
		pPanel->setScale(2.0);
#endif
		//add a btn to gui
		CCTexture2D* pPicNormal = CCTextureCache::sharedTextureCache()->addImage("CloseNormal.png");
		CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("CloseSelected.png");
		CPushButton* pBtn = new CPushButton();
		pBtn->setNormalPic(pPicNormal);
		pBtn->setClickPic(pPicSel);
		
		pBtn->setRect(CreateCRect(size.width - pPicSel->getContentSize().width,size.height - pPicSel->getContentSize().height,
					pPicSel->getContentSize().width,pPicSel->getContentSize().height));
		pBtn->setBkColor(CreateCColor(255,255,255,128));
		pBtn->setZOrder(1);
		pBtn->setcmdID(HelloWorld::CMD_ID_EIXT);
		m_pGUI->add(pBtn);


		CSorllPanel* pSrollPanel = new CSorllPanel();
		pSrollPanel->setBkColor(CreateCColor(128,128,128,255));
		pSrollPanel->setRect(CreateCRect(0,0,300,300));
		m_pGUI->add(pSrollPanel);


		CColor4B color(0,0,0,255); 
		CRectange rc(0,0,200,45);
		for (int index = 0;index < 50;index++)
		{
			CPanel* p1 = new CPanel();
			p1->setBkColor(color);
			p1->setRect(rc);
			pSrollPanel->add(p1);
			rc.origin.y += 50;
			color.r += 5;
			if (color.r > 255)
			{
				color.r = 255;
				color.g += 5;
				if (color.g > 255)
				{
					color.g = 255;
					color.b += 5;
					if (color.b > 255)
					{
						color.b = 255;
					}
				}
			}
			
		}
		//registe handler
		m_MyCmdHandler.addInterestCmdID(HelloWorld::CMD_ID_EIXT);
		CCommandHandlerMgr::instance()->addCmdHander(&m_MyCmdHandler);

        CC_BREAK_IF(! CCLayer::init());
		this->setTouchEnabled(true);

        bRet = true;

		CApplication::getInstance()->onCreate();
		this->scheduleUpdate();
    } while (0);
    return bRet;
}


void HelloWorld::registerWithTouchDispatcher(void)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(m_pGUI, INT_MIN + 1, false);
}

void HelloWorld::draw()
{
	//TODO check me 
	//for the reason that
	//z-order < 0 draw first
	//then function HelloWorld::draw will be invoked after that
	//then z-order > 0 draw after if there is a full screen pic 
	//it may hidden the GUI system
	m_pGUI->draw();
}


void HelloWorld::update(float delta)
{
	m_pGUI->logic(delta);
}


//////////////////////////////////////////////////////////////////////////
//for test using only
MyCCommandHandler::MyCCommandHandler()
{

}

MyCCommandHandler::~MyCCommandHandler()
{

}

void MyCCommandHandler::handleCmd(CUICommand& cmd)
{
	switch(cmd.getCmdID())
	{
	case HelloWorld::CMD_ID_EIXT:
		{
			LOG("in MyCCommandHandler b4 end");
			CCDirector::sharedDirector()->end();
			LOG("in MyCCommandHandler af end");
			break;
		}
	default:break;
	}
}
//////////////////////////////////////////////////////////////////////////