#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "ControlComponent.h"
#include <time.h>
#include <SDL_net.h>
#include <string>
#include "Packet.h"
#include "NetworkIDComponent.h"
#include "CollisionComponent.h"
#include "EventListener.h"
#include "MovementComponent.h"
#include "WeaponComponent.h"
#include "AttributesComponent.h"

class NetworkSystem : public System
{
public:
	NetworkSystem();
	NetworkSystem(EventListener *listener);

	void Update() {}
	void Update(float deltaTime);

	bool connectToServer();
	void disconnectFromServer();
	void listen();
	void send(Packet packet);
	bool getConnected();
	void setHost(bool host);
	bool getHost();
	// int getServetTime();
	// void setServerTime(Uint32 serverTime)
	int getServerSeed();
	int getID();
	void init();

	void LoadComponent() {}
	void UnloadComponent(int x) {}

private:
	bool m_connected;
	Uint32 m_serverTimeout;
	Uint32 m_serverTimeOffset;
	Uint8 m_packetSize;

	UDPsocket m_socket;
	UDPpacket* m_packet;

	IPaddress m_serverIP;
	Uint16 m_serverPort = 5228;

	//std::string m_hostIP = "149.153.106.156";
	std::string m_hostIP = "127.0.0.1";

	int m_timeout;

	bool m_isHost;

	int m_serverSeed;
	int m_id;

	float m_timeTilNextPacket;
	float m_maxTimeTilNextPacket;

	EventListener *m_listener;
};