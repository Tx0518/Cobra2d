#ifndef _C_CODE_TRANS_HELPER_H__
#define _C_CODE_TRANS_HELPER_H__
/************************************************************************/
/* using iconv lib to convert encoding form each other
/************************************************************************/
class CCodeTransHelper
{
public:
#if 0
	static bool gb2312TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
	static bool utf_8TOgb2312(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
#endif
	static bool utf_8TOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
	static bool utf_8TOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);

#if 0
	static bool gb2312TOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
	static bool gb2312TOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
#endif
	static bool utf_16TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
	static bool utf_32TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
#if 0
	static bool GBKTOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
	static bool GBKTOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
#endif
private:
	static bool code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);
};

#endif//_C_CODE_TRANS_HELPER_H__