#ifndef _CWEBSOCKET_H_
#define _CWEBSOCKET_H_

#include "cocos2d.h"
#include "network\WebSocket.h"
#include <iostream>
USING_NS_CC;


class CWebSocket: public cocos2d::network::WebSocket::Delegate
{
public:
	CWebSocket();
	virtual ~CWebSocket();

	void onSendMessage();
private:
	virtual void onOpen(cocos2d::network::WebSocket *pWs);
	virtual void onMessage(cocos2d::network::WebSocket *pWs, const cocos2d::network::WebSocket::Data &data);
	virtual void onClose(cocos2d::network::WebSocket *pWs);
	virtual void onError(cocos2d::network::WebSocket *pWs, const cocos2d::network::WebSocket::ErrorCode &error);

	cocos2d::network::WebSocket *m_pWsiSendText;
};




#endif