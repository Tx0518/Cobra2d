#include "CStringUtils.h"

namespace String_Utils
{


	std::string joinIntBySymbol( const std::vector<unsigned int>& vecInt,const char* symbol )
	{
		std::string content;
		std::vector<unsigned int>::const_iterator listItor;
		for (listItor = vecInt.begin();listItor!=vecInt.end();listItor++)
		{
			content += (*listItor);
			content += symbol;
		}
		return content;
	}

}