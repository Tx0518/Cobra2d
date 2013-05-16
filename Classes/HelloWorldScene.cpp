#include "HelloWorldScene.h"
#include "CApplication.h"
#include <map>
#include "CPanel.h"
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
		m_pGUI->setRect(CCRectMake(200,100,size.width/2,size.height/2));
		m_pGUI->setBkColor(ccc4(255,0,0,255));
		//add panel to gui
		CPanel* pPanel = new CPanel();
		pPanel->setBkColor(ccc4(0,255,0,255));
		pPanel->setRect(CCRectMake(100,100,100,50));
		m_pGUI->add(pPanel);

		//add panel2 to panel1
		CPanel* pPanel2 = new CPanel();
		pPanel2->setBkColor(ccc4(0,0,255,128));
		pPanel2->setRect(CCRectMake(25,25,180,10));
		pPanel->add(pPanel2);


        CC_BREAK_IF(! CCLayer::init());
		this->setTouchEnabled(true);
        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);


        bRet = true;

		CApplication::getInstance()->onCreate();

    } while (0);
    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
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