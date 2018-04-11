#include "MyWebSocket.h"


CWebSocket::CWebSocket()
{
	m_pWsiSendText = new cocos2d::network::WebSocket();
	m_pWsiSendText->init(*this, "ws://127.0.0.1:8000");
	
}

void CWebSocket::onSendMessage()
{
	m_pWsiSendText->send("Hello WebSocket, I'm a text message.");
}

CWebSocket::~CWebSocket()
{

}


void CWebSocket::onOpen(cocos2d::network::WebSocket *pWs)
{
	//std::cout << "连接成功" << std::endl;
	std::cout << pWs << std::endl;
	CCLOG("onOpen");
}

void CWebSocket::onMessage(cocos2d::network::WebSocket *pWs, const cocos2d::network::WebSocket::Data &data)
{
	std::cout << "收到消息" << std::endl;
	std::string textStr = data.bytes;
	CCLOG(textStr.c_str());
	//std::cout << pWs << std::endl;
}

void CWebSocket::onClose(cocos2d::network::WebSocket *pWs)
{
	std::cout << pWs << std::endl;
	if (pWs == m_pWsiSendText)
	{
		m_pWsiSendText = NULL;
	}
	CC_SAFE_DELETE(pWs);
}

void CWebSocket::onError(cocos2d::network::WebSocket *pWs, const cocos2d::network::WebSocket::ErrorCode &error)
{
	if (pWs == m_pWsiSendText)
	{
		char buf[100] = { 0 };
		sprintf(buf, "an error was fired, code: %d", error);
	}
	CCLOG("Error was fired, error code: %d", error);
}