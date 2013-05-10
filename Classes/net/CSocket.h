#ifndef _CSOCKET_H_
#define _CSOCKET_H_

#ifdef WIN32
#include <WinSock2.h>
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#endif

#define SOCKET int

#define SOCKET_TIMEOUT 30				//超时
#define _MAX_MSGSIZE 16 * 1024		// 暂定一个消息最大为16k
#define BLOCKSECONDS	30			// INIT函数阻塞时间
#define INBUFSIZE	(64*1024)		//?	具体尺寸根据剖面报告调整  接收数据的缓存

#define OUTBUFSIZE	(8*1024)		//? 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一 

#define MAX_RECV_BUFFERSIZE 65535

#pragma warning (disable: 4786)

#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef CHECKF
#define CHECKF(x) \
	do \
{ \
	if (!(x)) { \
	log_msg("CHECKF", #x, __FILE__, __LINE__); \
	return 0; \
	} \
} while (0)
#endif


#pragma comment(lib, "ws2_32.lib")

/************************************************************************/
/* 
	CSocket
*/
class CSocket
{
public:
	CSocket(void);
	~CSocket(void);
	bool	create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	bool	sendMsg(void* pBuf, int nSize);
	bool	receiveMsg(void* pBuf, int& nSize);
	bool	Flush(void);
	bool	Check(void);
	void	Destroy(void);
	SOCKET getSocket(void) const { return m_sockClient; }
private:
	bool	  recvFromSock(void);			// 从网络中读取尽可能多的数据
	bool    hasError();							// 是否发生错误，注意，异步模式未完成非错误
	void    closeSocket();

	SOCKET	m_sockClient;

	// 发送数据缓冲
	char	m_bufOutput[OUTBUFSIZE];		//? 可优化为指针数组
	int		m_nOutbufLen;

	// 环形缓冲区
	char	m_bufInput[INBUFSIZE];
	int		m_nInbufLen;
	int		m_nInbufStart;							// INBUF使用循环式队列，该变量为队列起点，0 - (SIZE-1)
};

/************************************************************************/
#endif  //_CSOCKET_H_