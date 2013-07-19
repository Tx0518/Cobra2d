#include "HelloWorldScene.h"
#include "CApplication.h"
#include <map>
#include "CPanel.h"
#include "CSorllPanel.h"
#include "CPushButton.h"
#include "CImageWidget.h"
#include "CLayoutParam.h"
#include "CLinearLayout.h"
#include "CActionMoveBy.h"
#include "CActionMoveTo.h"
#include "CActionFadeTo.h"
#include "CActionScaleTo.h"
#include "CActionSpwan.h"
#include "CLabel.h"
#include "CGraphic.h"
#include "CIntent.h"
#include "GameApplication.h"
#include "CBundle.h"
#include <string>
#include "CPropertyHelper.h"
#include "CHttpAdapter.h"
#include "CHttpRequest.h"
#include "CLoader.h"
#include "CCobraArray.h"
#include "CSTLHelper.h"
#include "ThreadExmaple.h"
#include "CBundle.h"
//////////////////////////////////////////////////////////////////////////
#include "CRichText.h"
//////////////////////////////////////////////////////////////////////////
#include "CSimpleAdapter.h"
#include "CSimpleList.h"
//////////////////////////////////////////////////////////////////////////
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
		m_pGUI->setRect(CreateCRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
		m_pGUI->setBkColor(CreateCColor(0,0,0,255));
		//add panel to gui
 		CPanel* pPanel = new CPanel();
 		pPanel->setBkColor(CreateCColor(0,255,0,255));
		pPanel->setRect(CreateCRect(200,200,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
 		
 		pPanel->setZOrder(0);
 		m_pGUI->add(pPanel);
// 
// 		//add panel2 to panel1
// 		CPanel* pPanel2 = new CPanel();
// 		pPanel2->setBkColor(CreateCColor(0,0,255,128));
// 		pPanel2->setRect(CreateCRect(0,25,100,10));
// 		pPanel->add(pPanel2);
// 		//set scale to parent all child will be effected!!
// 		pPanel->setScale(2.0);
// 		//add a btn to gui
 		CCTexture2D* pPicNormal = CCTextureCache::sharedTextureCache()->addImage("CloseNormal.png");
 		CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("CloseSelected.png");
 		CPushButton* pBtn = new CPushButton();
 		pBtn->setNormalPic(pPicNormal);
 		pBtn->setClickPic(pPicSel);
 		
 		pBtn->setRect(CreateCRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
 		//pBtn->setScale(1.0f);
 		pBtn->setZOrder(1);
 		pBtn->setcmdID(HelloWorld::CMD_ID_EIXT);
		pBtn->setlongClick(true,1234567);
		pPanel->add(pBtn);
// 
// 
// 
// 		m_pGUI->add(pBtn);
// 		CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("CloseSelected.png");
// 		CImageWidget* pImage = new CImageWidget();
// 		pImage->setPic(pPicSel);
// 		pImage->setRect(CreateCRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
// 		pPanel->add(pImage);

		//for test using 
		//do not care memory link here!!!
		CActionMoveBy* pMoveBy = new CActionMoveBy();
		pMoveBy->init(2,CreateCPoint(100,100));
		

		CActionMoveTo* pMoveTo = new CActionMoveTo();
		pMoveTo->init(2,CreateCPoint(100,100));

		CActionFadeTo* pFade = new CActionFadeTo();
		pFade->init(2,0);

		CActionScaleTo* pScale = new CActionScaleTo();
		
		
		pScale->init(2,1);
		//pPanel->setScale(0);
		pPanel->runAction(pMoveTo);


		CLabel* pLabel = new CLabel();
		pLabel->setString(std::string("HelloWorld"),20,CreateCColor(255,0,0,255),std::string("宋体"));
		pLabel->setPos(100,0);
		CActionSpwan* pSpwan = new CActionSpwan();
		pSpwan->initWidthActions(pMoveBy,pFade);
		pLabel->runAction(pSpwan);
		m_pGUI->add(pLabel);

				//registe handler
		m_MyCmdHandler.addInterestCmdID(HelloWorld::CMD_ID_EIXT);
		CCommandHandlerMgr::instance()->addCmdHander(&m_MyCmdHandler);
        CC_BREAK_IF(! CCLayer::init());
		this->setTouchEnabled(true);

        bRet = true;

		GameApplication application;
		application.onCreate();
		application.didEnterApplication();


// 		CHttpRequest request1;
// 		request1.setRequestUrl("http://h.hiphotos.baidu.com/album/w%3D1366%3Bcrop%3D0%2C0%2C1366%2C768/sign=83acd2dbfaedab64747249c3c10094a0/c83d70cf3bc79f3ddf7f4820bba1cd11728b2907.jpg");
// 		request1.setSaveTargerFileAddr("download1.jpg");

// 		CLoader loader;
// 		loader.load(&request1);

		this->testRichTxt();
		//this->testLinearLayout();
		this->testSimpleList();
		this->scheduleUpdate();

		ZThread::Thread t(new ThreadExample());

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

void HelloWorld::testRichTxt( void )
{
	CRichTxtFormater formater("宋体",25,0x000000ff);

	
 	std::string str=  "\nhello \n \nworld,this is a test string!";
 	formater.addText(CLabel::E_TXT_TYPE_LINK,str,0,0,false);

	std::string str2=  "you are the chosen one";
 	formater.addText(CLabel::E_TXT_TYPE_RAW,str2,40,0xffff00ff);
	//////////////////////////////////////////////////////////////////////////
	CRichTxtLayOut layout;
	layout.init(200);
	layout.setTxt(formater.getRichText());

	int iWidth = layout.getWidth();
	int iHeight = layout.getHeight();

	CSorllPanel* pPanel = new CSorllPanel();
	pPanel->setRect(CreateCRect(200,0,200,250));
	pPanel->setSorllType(CSorllPanel::E_SORLL_TYPE_HORI | CSorllPanel::E_SORLL_TYPE_VERTI);
	m_pGUI->add(pPanel);
	layout.attachToPanel(pPanel);
	//pPanel->setSorllAble(false);
}

void HelloWorld::testLinearLayout(void)
{
	CLinearLayout* pLayout = new CLinearLayout();
	pLayout->setRect(0,0,400,100);
	pLayout->setSorllType(CSorllPanel::E_SORLL_TYPE_HORI | CSorllPanel::E_SORLL_TYPE_VERTI);
	pLayout->setBkColor(0xff0000ff);
	//////////////////////////////////////////////////////////////////////////
	pLayout->setPadding(10,10,10,10);

#if 0
	int index = 0;
	int count = 20;
	CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("CloseSelected.png");
	for (;index < count;index++)
	{
		CImageWidget* pImage = new CImageWidget();
		pImage->setPic(pPicSel);
		pImage->setRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT);
		pLayout->add(pImage);
	}
#else
	CImageWidget* pImage = new CImageWidget();
	CCTexture2D* pPicSel = CCTextureCache::sharedTextureCache()->addImage("cj0004.jpg");
	pImage->setPic(pPicSel);
	pImage->setRect(0,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT);
	pLayout->add(pImage);
#endif
	m_pGUI->add(pLayout);


	
// 	CActionMoveTo* pMoveTo = new CActionMoveTo();
// 	pMoveTo->init(2,CreateCPoint(100,100));
// 
// 	CActionFadeTo* pFade = new CActionFadeTo();
// 	pFade->init(2,100);
// 
// 	CActionSpwan* pSpwan = new CActionSpwan();
// 	pSpwan->initWidthActions(pMoveTo,pFade);
// 
// 	pLayout->runAction(pSpwan);
//
}

void HelloWorld::testSimpleList( void )
{
	CSimpleList* pList = new CSimpleList();
	CSimpleAdapter* pAdapter = new CSimpleAdapter();	
	//////////////////////////////////////////////////////////////////////////
	CSimpleAdapter::AdapterData data;

	std::map<std::string,std::string> mapTemp;
	mapTemp["image"] = "CloseSelected.png";
	mapTemp["btn_normal"] = "CloseNormal.png";
	mapTemp["btn_sel"] = "CloseSelected.png";
	
	int index = 0;
	int count = 10;
	std::string strTemp;
	for (;index < count;index++)
	{
		strTemp = "hello" + CPropertyHelper::intToString(index);
		mapTemp["text"] = strTemp;
		data.push_back(mapTemp);
	}
	//////////////////////////////////////////////////////////////////////////

	CSimpleAdapter::AdapterLayoutInfo layoutInfo;

	CLayoutInfo* pImageInfo = new CLayoutInfo();
	pImageInfo->setWidgetID(1);
	pImageInfo->setWidgetType(CImageWidget::IMAGE_WIDGET_TYPE);
	pImageInfo->setWidgetRc(CreateCRect(0,10,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));

	CLayoutBtnInfo* pBtnInfo = new CLayoutBtnInfo();
	pBtnInfo->setWidgetID(2);
	pBtnInfo->setCmdID(2222);
	pBtnInfo->setWidgetRc(CreateCRect(50,50,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));

	CLayoutLabelInfo* pLabelInfo = new CLayoutLabelInfo();
	pLabelInfo->setWidgetID(4);
	pLabelInfo->setFontColor(0xff0000ff);
	pLabelInfo->setFontSize(20);
	pLabelInfo->setFontName("宋体");
	pLabelInfo->setWidgetRc(CreateCRect(40,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));


	layoutInfo.push_back(pImageInfo);
	layoutInfo.push_back(pBtnInfo);
	layoutInfo.push_back(pLabelInfo);

	//////////////////////////////////////////////////////////////////////////
	CSimpleAdapter::FromKeySet fromKeySet;
	fromKeySet.push_back("image");
	fromKeySet.push_back("btn_normal");
	fromKeySet.push_back("btn_sel");
	fromKeySet.push_back("text");
	//////////////////////////////////////////////////////////////////////////
	CSimpleAdapter::ToPropertySet toSet;

	toSet.push_back(std::make_pair<int,std::string>(1,CImageWidget::IMAGE_PIC));
	toSet.push_back(std::make_pair<int,std::string>(2,CPushButton::PB_NORMAL_PIC));
	toSet.push_back(std::make_pair<int,std::string>(2,CPushButton::PB_CLICK_PIC));
	toSet.push_back(std::make_pair<int,std::string>(4,CLabel::LABEL_STR));
	//////////////////////////////////////////////////////////////////////////
	pAdapter->init(data,layoutInfo,fromKeySet,toSet);

	pList->setRect(10,10,200,200);
	pList->setAdataper(pAdapter);
	m_pGUI->add(pList);

	CActionMoveTo* pMoveTo = new CActionMoveTo();
	pMoveTo->init(2,CreateCPoint(100,100));
	pList->runAction(pMoveTo);
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