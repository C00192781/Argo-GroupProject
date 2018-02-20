#pragma once

#include <SDL_net.h>
#include <string>

class Client
{
public:
	Client();
	~Client();

	void connectToServer();
	void disconnectFromServer();
	void listen();
	//void send(PacketData packet)
	bool getConnected();
	// int getServetTime();
	// void setServerTime(Uint32 serverTime)

private:
	bool m_connected;
	Uint32 m_serverTimeout;
	Uint8 m_packetSize;

	UDPsocket m_socket;
	UDPpacket* m_packet;

	IPaddress m_serverIP;
	Uint16 m_serverPort;

	//bool m_connected;
	//Uint32 m_serverTimeout;
	//Uint8 m_packetSize;
	//
	//UDPsocket m_socket;
	//UDPpacket* m_packet;
	//
	//IPaddress m_serverIP;
	IPaddress m_clientIP;
	Uint16 m_clientPort;
	//Uint16 m_serverPort;
	//
	//Uint32 m_lastConnectionTime;
	//Uint32 m_currentConnectionTime;
	//bool m_connectionWaiting;
	//Uint8 m_connectionRetry;
	//Uint16 m_ping;
	//Uint8 m_roomID;
};