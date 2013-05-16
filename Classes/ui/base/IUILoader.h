#ifndef __I_UI_LOADER_H__
#define __I_UI_LOADER_H__
/************************************************************************/
/* this file is used to define the UI LOADER interface
*/
/************************************************************************/
#include "CHashHelper.h"
class IUILoader
{
	virtual bool load(std::string& str)=0;
	virtual bool setPorperty(const std::string& key,const std::string& strvalue)=0;
};
#endif //__I_UI_LOADER_H__