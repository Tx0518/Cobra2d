#ifndef __C_LIST_WIDGET_H__
#define __C_LIST_WIDGET_H__

/************************************************************************/
/* this class is a simple list view to use this class
TODO:
*/
/************************************************************************/
class CListCell :public CPanel
{
public:
	CListCell();
	virtual ~CListCell();
	void init();
	//////////////////////////////////////////////////////////////////////////
	void handlePenDown(CWidgetEvent& event);
	void handlePenUp(CWidgetEvent& event);
	void handlePenClick(CWidgetEvent& event);
	void draw(CGraphic* pGraphic);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY_UNIMPLEMENT(CCTexture2D*,m_pBkPicSel,BkPicSelected)
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bCellClickAble,CellClickAble)
	COBRA_CREATE_PROPERTY_BY_BOOL_UNIMPLEMENT(bool,m_bClicked,Clicked)
	COBRA_CREATE_PROPERTY(int,m_cmdID,cmdID)
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* how to use:
//create a list
CSimpleList* pList = new CSimpleList();
//create a adapter
CSimpleAdapter* pAdapter = new CSimpleAdapter();	
//////////////////////////////////////////////////////////////////////////
//init adapter data
CSimpleAdapter::AdapterData data;
//for each line create each data
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
//init layout information
//the widget id must be unique
CSimpleAdapter::AdapterLayoutInfo layoutInfo;

//this is a image
CLayoutInfo* pImageInfo = new CLayoutInfo();
pImageInfo->setWidgetID(1);
pImageInfo->setWidgetType(CImageWidget::IMAGE_WIDGET_TYPE);
pImageInfo->setWidgetRc(CreateCRect(0,10,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));
//this is a button
CLayoutBtnInfo* pBtnInfo = new CLayoutBtnInfo();
pBtnInfo->setWidgetID(2);
pBtnInfo->setCmdID(2222);
pBtnInfo->setWidgetRc(CreateCRect(50,50,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));

//this is a label
CLayoutLabelInfo* pLabelInfo = new CLayoutLabelInfo();
pLabelInfo->setWidgetID(4);
pLabelInfo->setFontColor(0xff0000ff);
pLabelInfo->setFontSize(20);
pLabelInfo->setFontName("ËÎÌו");
pLabelInfo->setWidgetRc(CreateCRect(40,0,CLayoutParam::WRAP_CONTENT,CLayoutParam::WRAP_CONTENT));


layoutInfo.push_back(pImageInfo);
layoutInfo.push_back(pBtnInfo);
layoutInfo.push_back(pLabelInfo);

//////////////////////////////////////////////////////////////////////////
//init the key set
CSimpleAdapter::FromKeySet fromKeySet;
fromKeySet.push_back("image");
fromKeySet.push_back("btn_normal");
fromKeySet.push_back("btn_sel");
fromKeySet.push_back("text");
//////////////////////////////////////////////////////////////////////////
//init property set
CSimpleAdapter::ToPropertySet toSet;
//widget id  
//widget property
toSet.push_back(std::make_pair<int,std::string>(1,CImageWidget::IMAGE_PIC));
toSet.push_back(std::make_pair<int,std::string>(2,CPushButton::PB_NORMAL_PIC));
toSet.push_back(std::make_pair<int,std::string>(2,CPushButton::PB_CLICK_PIC));
toSet.push_back(std::make_pair<int,std::string>(4,CLabel::LABEL_STR));
//////////////////////////////////////////////////////////////////////////
//invoke init method
pAdapter->init(data,layoutInfo,fromKeySet,toSet);
//set rectangle for list
pList->setRect(10,10,200,200);
//set adapter
pList->setAdataper(pAdapter);
*/
/************************************************************************/
class CSimpleList :public CSorllPanel
{
public:
	//typedef std::deque<CListCell*>  CellDeque;
	//typedef std::deque<CListCell*>::iterator CellDequeIter;
	CSimpleList(void);
	virtual ~CSimpleList(void);
	//set cell property
	//@in bCellClickAble can be clicked or not
	//@in iCellCmdID is can clicked this cmd will be sent
	void setCellProperty(bool bCellClickAble,int iCellCmdID);
	void setCellBk(CCTexture2D* pPicNormal,CCTexture2D* pPicSel = NULL);
	//setAdataper
	//@in pAdapter data adapter
	//@in bOwnData default is true pAdapter will be deleted when CListWidget deleted
	bool setAdataper(CSimpleAdapter* pAdapter,bool bOwnData = true);
private:
	void clearAdataper(void);
	void layoutChildren(void);
	//////////////////////////////////////////////////////////////////////////
	//CellDeque m_cellDeque;
	bool	  m_bCanClickCell;
	int       m_iCellCmdID;
	CCTexture2D* m_pCellBkNormal;
	CCTexture2D* m_pCellBkSel;
	//////////////////////////////////////////////////////////////////////////
	CSimpleAdapter* m_pAdapter;
	bool	  m_bOwnedAdapter;
	//////////////////////////////////////////////////////////////////////////

};
#endif //__C_LIST_WIDGET_H__
