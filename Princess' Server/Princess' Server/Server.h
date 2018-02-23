#pragma once

#include <SDL_net.h>
#include <map>
#include "ClientInfo.h"
#include "Client.h"
#include "Packet.h"
#include <iostream>
#include <time.h>
#include <random>

class Server
{
public:
	Server();
	~Server() {}

	void update();

	bool send(const int &id, Packet packet);
	void sendToAll(Packet packet);
	void sendToOtherClients(Packet packet, int id);
	void listen();

	//void broadcastToRoomOnly(Packet& packetData, const Uint8 & roomID, const int& ignoreClientID = -1);
	//void broadcastToLobbyOnly(Packet& packetData, const Uint8 & roomID, const int& ignoreClientID = -1);
	//void broadcastToEveryone(Packet& packetData, const int& ignoreClientID = -1);

	int addClient(Uint32 &ip, Uint16 &port);
	//bool removeClient(const int& clientID);
	bool removeClient(int id);
	int getID(const Uint32 &ip, const Uint16 &port);

	void disconnectAllClients();

	bool start();
	bool stop();
	bool getRunning();

	void handlePacket(Uint32 &ip, Uint16 &port, Uint8 &packetType, Packet &packet);

private:
	const int m_maxNumberOfClients = 4;

	int m_port;
	
	bool m_running;
	int m_nextClientID;
	int m_totalDataSent;
	int m_totalDataReceived;

	Uint8 m_packetSize;

	UDPsocket m_socket;
	UDPpacket * m_packet;

	std::map<int, ClientInfo> m_clients;
	Uint32 m_uptime;

	const unsigned short m_serverPort = 5228;

	int m_seed;
};