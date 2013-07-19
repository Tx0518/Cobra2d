#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "CGui.h"
#include "CommandHandlerMgr.h"

class MyCCommandHandler:public CCommandHandler
{
public: 
	MyCCommandHandler();
	~MyCCommandHandler();
	 void handleCmd(CUICommand& cmd);
};

class HelloWorld : public cocos2d::CCLayer
{
public:
	//////////////////////////////////////////////////////////////////////////
	static const int CMD_ID_EIXT = 12345;
	//////////////////////////////////////////////////////////////////////////
	
	~HelloWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	//////////////////////////////////////////////////////////////////////////
	virtual void registerWithTouchDispatcher(void);
	//////////////////////////////////////////////////////////////////////////
	
	void draw();

	void update(float delta);
private:
	void testRichTxt(void);
	void testLinearLayout(void);
	void testSimpleList(void);
	CGui* m_pGUI;
	MyCCommandHandler m_MyCmdHandler;
};

#endif  // __HELLOWORLD_SCENE_H__