#include "CCodeTransHelper.h"
#include <string>
#include "iconv.h"


//////////////////////////////////////////////////////////////////////////
#if 0
bool CCodeTransHelper::gb2312TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("gb2312","utf-8",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////
bool CCodeTransHelper::gb2312TOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("gb2312","utf-16le",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}


bool CCodeTransHelper::utf_8TOgb2312(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("utf-8","gb2312",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}
#endif

bool CCodeTransHelper::utf_8TOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("utf-8","UTF-32LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}

bool CCodeTransHelper::utf_8TOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("utf-8","UTF-16LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
bool CCodeTransHelper::utf_16TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("UTF-16LE","utf-8",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}

bool CCodeTransHelper::utf_32TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("UTF-32LE","utf-8",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
#if 0
bool CCodeTransHelper::gb2312TOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("gb2312","UTF-32LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
bool CCodeTransHelper::GBKTOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("GBK","UTF-16LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}

bool CCodeTransHelper::GBKTOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength)
{
	bool ret = false;
	if (pStrIn && pOutBuffer)
	{
		ret = CCodeTransHelper::code_convert("GBK","UTF-32LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
	}
	return ret;
}
#endif
//////////////////////////////////////////////////////////////////////////
bool CCodeTransHelper::code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
{
	bool ret  = false;
	iconv_t cd = 0;
	/*const */char *temp = inbuf;
	/*const */char **pin = &temp;
	char **pout = &outbuf;
	do 
	{
		cd = iconv_open(to_charset,from_charset);
		if (0 == cd)
		{
			break;
		}
		memset(outbuf,0,outlen);
		size_t tempInlength = inlen;
		size_t tempOutLength = outlen;
		if(-1 == iconv(cd,pin,&tempInlength,pout,&tempOutLength))
		{
			break;
		}

		iconv_close(cd);
		ret = true;
	} while (0);
	return ret;
}
