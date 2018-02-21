#pragma once

#include <SDL.h>
#include <SDL_net.h>
#include <string>
#include "Packet.h"

class Client
{
public:
	Client();
	~Client() {};

	bool connectToServer();
	void disconnectFromServer();
	void listen();
	void send(Packet packet);
	bool getConnected();
	void setHost(bool host);
	bool getHost();
	// int getServetTime();
	// void setServerTime(Uint32 serverTime)

private:
	bool m_connected;
	Uint32 m_serverTimeout;
	Uint32 m_serverTimeOffset;
	Uint8 m_packetSize;

	UDPsocket m_socket;
	UDPpacket* m_packet;

	IPaddress m_serverIP;
	Uint16 m_serverPort = 5228;

	std::string m_hostIP = "149.153.106.156";

	int m_timeout;

	bool m_isHost;

	//bool m_connected;
	//Uint32 m_serverTimeout;
	//Uint8 m_packetSize;
	//
	//UDPsocket m_socket;
	//UDPpacket* m_packet;
	//
	//IPaddress m_serverIP;
	//Uint16 m_serverPort;
	//IPaddress m_clientIP;
	//Uint16 m_clientPort;
	//
	//Uint32 m_lastConnectionTime;
	//Uint32 m_currentConnectionTime;
	//bool m_connectionWaiting;
	//Uint8 m_connectionRetry;
	//Uint16 m_ping;
	//Uint8 m_roomID;
};