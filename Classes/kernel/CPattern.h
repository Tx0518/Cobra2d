#ifndef _CPATTERN_H_
#define _CPATTERN_H_


class CResponse;
/************************************************************************/
/* 
	IResponseReciver
*/
class IResponseReciver
{
public:
	virtual void onResponseHandler(CResponse* response) = 0;
};

/************************************************************************/

#endif	//_CPATTERN_H_