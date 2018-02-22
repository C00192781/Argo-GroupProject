#include "NetworkSystem.h"

NetworkSystem::NetworkSystem()
{
	m_connected = false;
	m_serverTimeOffset = 0;
	m_serverTimeout = 3000;
	m_packetSize = std::numeric_limits<Uint8>::max();
	m_isHost = false;
	m_id = -1;

	if (connectToServer())
	{
		init();
		srand(getServerSeed());
		m_active = true;
	}
	else
	{
		srand(time(NULL));
		m_active = false;
	}

	m_maxTimeTilNextPacket = 0.02;
	m_timeTilNextPacket = 0;
}

void NetworkSystem::Update(float deltaTime)
{
	listen();

	if (m_timeTilNextPacket > m_maxTimeTilNextPacket)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			PositionComponent* positionComponent = static_cast<PositionComponent*>(m_entities.at(i)->FindComponent("PC"));
			ControlComponent* controlComponent = static_cast<ControlComponent*>(m_entities.at(i)->FindComponent("control"));

			if (m_entities.at(i)->ID() == "Player" && controlComponent != nullptr)
			{
				Packet packet;

				packet << (Uint8)PacketType::UPDATEPLAYERS << getID() << positionComponent->getX() << positionComponent->getY();

				send(packet);
			}
		}

		m_timeTilNextPacket = 0;
	}
	else
	{
		m_timeTilNextPacket += deltaTime;
	}
}

void NetworkSystem::send(Packet packet)
{
	if (packet.getDataSize() > 0)
	{
		m_packet->len = packet.getDataSize();
		memcpy(m_packet->data, packet.getData(), m_packet->len);
		SDLNet_UDP_Send(m_socket, -1, m_packet);
	}
}

void NetworkSystem::listen()
{
	if (SDLNet_UDP_Recv(m_socket, m_packet) > 0)
	{
		Packet packet;
		packet.append(m_packet->data, m_packet->len);

		Uint8 packetType;
		packet >> packetType;

		if (packetType == (Uint8)PacketType::CONNECTIONALIVE)
		{
			Packet newPacket;
			newPacket << (Uint8)PacketType::CONNECTIONALIVE;
			send(newPacket);

			Uint32 serverTime;
			packet >> serverTime;
			m_serverTimeOffset = (serverTime - SDL_GetTicks());
		}
		else if (packetType == (Uint8)PacketType::UPDATEPLAYERS)
		{

		}
	}
}

bool NetworkSystem::connectToServer()
{
	if (m_connected == false)
	{
		if (SDLNet_Init() != -1)
		{
			m_socket = SDLNet_UDP_Open(0);

			SDLNet_ResolveHost(&m_serverIP, m_hostIP.c_str(), m_serverPort);

			m_packet = SDLNet_AllocPacket(m_packetSize);
			m_packet->address.host = m_serverIP.host;
			m_packet->address.port = m_serverIP.port;

			Packet packet;
			packet << (Uint8)PacketType::CONNECT;

			if (m_packet->len = packet.getDataSize() > 0)
			{
				memcpy(m_packet->data, packet.getData(), m_packet->len);
				SDLNet_UDP_Send(m_socket, -1, m_packet);
			}

			int currentTime = SDL_GetTicks();

			while (SDL_GetTicks() < (currentTime + m_serverTimeout))
			{
				if (SDLNet_UDP_Recv(m_socket, m_packet))
				{
					m_connected = true;

					return m_connected;
				}
			}

			SDLNet_UDP_Close(m_socket);
			m_socket = NULL;
		}
	}
	return m_connected;
}

void NetworkSystem::disconnectFromServer()
{
	if (m_connected == true)
	{
		m_connected = false;
		SDLNet_UDP_Close(m_socket);
		m_socket = NULL;
	}
}

void NetworkSystem::init()
{
	Packet packet;
	packet << (Uint8)PacketType::INIT;

	if (m_packet->len = packet.getDataSize() > 0)
	{
		memcpy(m_packet->data, packet.getData(), m_packet->len);
		SDLNet_UDP_Send(m_socket, -1, m_packet);
	}

	while (m_id < 0)
	{
		if (SDLNet_UDP_Recv(m_socket, m_packet) > 0)
		{
			Packet packet;
			packet.append(m_packet->data, m_packet->len);

			Uint8 packetType;
			packet >> packetType;

			if (packetType == (Uint8)PacketType::INIT)
			{
				packet >> m_id;
				packet >> m_serverSeed;
			}
		}
	}
}

bool NetworkSystem::getConnected()
{
	return m_connected;
}

void NetworkSystem::setHost(bool host)
{
	m_isHost = true;
}

bool NetworkSystem::getHost()
{
	return m_isHost;
}

int NetworkSystem::getServerSeed()
{
	return m_serverSeed;
}

int NetworkSystem::getID()
{
	return m_id;
}