#include "CBaseContainer.h"
#include "CSimpleAdapter.h"
#include <algorithm>
#include "CPlatFormDefine.h"
#include "CPushButton.h"
#include "CImageWidget.h"
#include "CLabel.h"

//////////////////////////////////////////////////////////////////////////
CLayoutInfo::CLayoutInfo()
{
	m_strWidgetType = "";
	m_iWidgetID  = 0;
	m_rcWidget   = RectZero;
}

CLayoutInfo::~CLayoutInfo()
{

}
//////////////////////////////////////////////////////////////////////////
CLayoutBtnInfo::CLayoutBtnInfo()
{
	m_iCmdID = 0;
	m_strWidgetType = CPushButton::PUSH_BTN_TYPE;
}

CLayoutBtnInfo::~CLayoutBtnInfo()
{

}
//////////////////////////////////////////////////////////////////////////
CLayoutLabelInfo::CLayoutLabelInfo()
{
	m_strWidgetType = CLabel::LABEL_TYPE;
	m_iFontSize  = 0;
	m_iFontColor = 0;
	m_strFontName = "";
}

CLayoutLabelInfo::~CLayoutLabelInfo()
{
	;//do nothing
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CSimpleAdapter::CSimpleAdapter(void)
{
	m_bInit = false;
}


CSimpleAdapter::~CSimpleAdapter(void)
{
	AdapterLayoutInfoIter iter = m_layoutInfo.begin();
	CLayoutInfo* pInfo = NULL;
	while(iter != m_layoutInfo.end())
	{
		pInfo = *iter;
		if (pInfo)
		{
			delete pInfo;
			pInfo = NULL;
		}
		iter++;
	}
}

bool CSimpleAdapter::init( AdapterData& data,AdapterLayoutInfo& layout,FromKeySet& from,ToPropertySet& to)
{
	ENTERFUNC();
	bool ret = false;
	ret = this->checkParam(data,layout,from,to);
	if (ret)
	{
		 m_Data = data;
		 m_layoutInfo = layout;
		 m_from = from;
		 m_to   = to;
		 m_bInit = true;
	}
	else
	{
		LOG("parameter is invalid do nothing here");
	}
	return ret;
	LVFUNC();
}

bool CSimpleAdapter::checkParam( AdapterData& data,AdapterLayoutInfo& layout,FromKeySet& from,ToPropertySet& to)
{
	ENTERFUNC();
	bool ret = false;
	do 
	{
		//check layout information and to 
		//widget ids of these two item must equal
		AdapterLayoutInfoIter iterLayout = layout.begin();
		while(iterLayout != layout.end())
		{
			ToPropertySetIter iter = to.begin();
			while(iter != to.end())
			{
				if (iter->first == (*iterLayout)->getWidgetID())
				{
					break;
				}
				iter++;
			}
			if (iter == to.end())
			{
				break;
			}
			iterLayout++;
		}

		if (iterLayout != layout.end())
		{
			LOG("parameter is invalid,layout's widget id can not find in \"fromTo\" array");
			break;
		}

		if (from.size() != to.size())
		{
			LOG("key set does not equal property size");
			break;
		}
	
		//last we check  data  array 
		//data array's item must have the same size of layout from and to
		//here only check one for the reason the pre-operation we did above just ensures the other condition
		AdapterDataIter iterData = data.begin();
		while(iterData != data.end())
		{
			std::map<std::string,std::string>& item = *iterData;
			if (item.size() < from.size())
			{
				break;
			}
			iterData++;
		}

		if (iterData != data.end())
		{
			LOG("parameter is invalid,data is invalid");
			break;
		}

		ret = true;
	} while (0);
	LVFUNC();
	return ret;
}
