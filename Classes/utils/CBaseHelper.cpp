#include "CBaseHelper.h"


namespace base_helper
{

	int getMaxIntValue(int first,int second )
	{
		if(first > second) return first;
		return second;
	}
}