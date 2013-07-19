#ifndef __C_SIMPLE_ADAPTER_H__
#define __C_SIMPLE_ADAPTER_H__
#include "CBaseWidget.h"
//////////////////////////////////////////////////////////////////////////
class CLayoutInfo
{
public:
	CLayoutInfo();
	virtual ~CLayoutInfo();
	//widget type
	COBRA_CREATE_PROPERTY(std::string,m_strWidgetType,WidgetType);
	//widget id
	COBRA_CREATE_PROPERTY(int,m_iWidgetID,WidgetID);
	//widget rectangle
	COBRA_CREATE_PROPERTY(CRectange,m_rcWidget,WidgetRc);
};

class CLayoutBtnInfo:public CLayoutInfo
{
public:
	CLayoutBtnInfo();
	virtual ~CLayoutBtnInfo();
	//cmd id for push button
	COBRA_CREATE_PROPERTY(int,m_iCmdID,CmdID);
};

class CLayoutLabelInfo:public CLayoutInfo
{
public:
	CLayoutLabelInfo();
	virtual ~CLayoutLabelInfo();
	//font size for label
	COBRA_CREATE_PROPERTY(int,m_iFontSize,FontSize);
	//font color for label
	COBRA_CREATE_PROPERTY(int,m_iFontColor,FontColor);
	//font name for label
	COBRA_CREATE_PROPERTY(std::string,m_strFontName,FontName);
};
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*!!all data used by this class owned by YOUSELF  you must manage your data 
this class only make a reference or copy
*/
/************************************************************************/
class CSimpleAdapter
{
public:
	//////////////////////////////////////////////////////////////////////////
	typedef std::vector<CLayoutInfo*> AdapterLayoutInfo;
	typedef AdapterLayoutInfo::iterator AdapterLayoutInfoIter;
	//Adapter data  for data 
	//@std::string key in AdapterFrom
	//@std::string value stands for values depends on different widget type
	typedef std::list<std::map<std::string,std::string> >  AdapterData;
	typedef AdapterData::iterator  AdapterDataIter;
	//////////////////////////////////////////////////////////////////////////
	//
	//Adapter From key data to widget id
	//@std::string key int AdapterData's map
	//@int widget id in layout info
	typedef std::vector<std::string>        FromKeySet;
	typedef FromKeySet::iterator            FromKeySetIter;


	//@int widget id
	//@std::string widget property
	//this std::pair<int,std::string> stands for one given widget's given property
	typedef std::pair<int,std::string>				 ToProperty;
	typedef std::vector<ToProperty>					 ToPropertySet;
	typedef ToPropertySet::iterator                  ToPropertySetIter;

	//typedef std::pair<std::string,int>               FromToInfo;
	//typedef std::vector<FromToInfo> AdapterFromTo;
	//typedef AdapterFromTo::iterator                  AdapterFromToIter;
	CSimpleAdapter(void);
	virtual ~CSimpleAdapter(void);
	//////////////////////////////////////////////////////////////////////////
	//@return true means true else you should check the parameter 
	//own data layout(you should no need control the layout you created)
	//@AdapterData  data source 
	//@AdapterLayoutInfo layout info for one cell
	//@FromKeySet key set in data data source 
	//@ToPropertySet property set in layout 
	//!!
	bool init(AdapterData& data,AdapterLayoutInfo& layout,FromKeySet& from,ToPropertySet& to);
	//////////////////////////////////////////////////////////////////////////
	friend class CSimpleList;
private:
	bool checkParam(AdapterData& data,AdapterLayoutInfo& layout,FromKeySet& from,ToPropertySet& to);
	AdapterData m_Data;
	AdapterLayoutInfo m_layoutInfo;
	FromKeySet  m_from;
	ToPropertySet m_to;
	bool	    m_bInit;
	//////////////////////////////////////////////////////////////////////////
};

#endif //__C_SIMPLE_ADAPTER_H__