#ifndef __IOCP_SERVER_H__
#define __IOCP_SERVER_H__

#include <list>

struct IoContext;
struct ClientContext;

class IocpServer
{
public:

    IocpServer(short listenPort);
    IocpServer(const IocpServer&) = delete;
    IocpServer& operator=(const IocpServer&) = delete;
    ~IocpServer();

    bool init();
    bool start();
    bool stop();

protected:
	//必须要static _beginthreadex才能访问
	static unsigned WINAPI IocpWorkerThread(LPVOID arg);

	bool createListenClient(short listenPort);
	bool createIocpWorker();

	bool postAccept(IoContext* pIoCtx);
    bool postRecv(IoContext* pIoCtx);
    bool postSend(IoContext* pIoCtx);
    bool postParse(ClientContext* pConnClient, IoContext* pIoCtx);

    bool handleAccept(ClientContext* pListenClient, IoContext* pIoCtx);
    bool handleRecv(ClientContext* pConnClient, IoContext* pIoCtx);
    bool handleSend(ClientContext* pConnClient, IoContext* pIoCtx);
    bool handleParse(ClientContext* pConnClient, IoContext* pIoCtx);

    void addClient(ClientContext* pConnClient);

private:
	short						m_listenPort;
	HANDLE						m_comPort;              //完成端口
	ClientContext*				m_pListenClient;
	std::list<ClientContext*>	m_connList;             //已连接客户端列表
    CRITICAL_SECTION            m_csConnList;           //保护连接列表

	void*						m_lpfnAcceptEx;		    //acceptEx函数指针
    void*                       m_lpfnGetAcceptExAddr;  //GetAcceptExSockaddrs函数指针

	int							m_nWorkerCnt;           //io工作线程数量
};











#endif // !__IOCP_SERVER_H__

