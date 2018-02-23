#pragma once

#include <SDL.h>

class ClientInfo
{
public:
	ClientInfo(const Uint32 & ip, const Uint16 & port, const Uint32 serverTime)
		: m_clientIP(ip)
		, m_clientPort(port)
		, m_lastConnectionTime(serverTime)
		, m_currentConnectionTime(serverTime)
		, m_connectionWaiting(false)
		, m_connectionRetry(0)
		, m_ping(0)
	{}

	Uint32 m_clientIP;
	Uint16 m_clientPort;
	Uint32 m_lastConnectionTime;
	Uint32 m_currentConnectionTime;
	bool m_connectionWaiting;
	Uint8 m_connectionRetry;
	Uint16 m_ping;
	//Uint8 m_roomID;
};