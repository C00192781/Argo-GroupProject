#include "Client.h"
#include <iostream>

Client::Client()
{
	m_connected = false;
	m_serverTimeOffset = 0;
	m_serverTimeout = 3000;
	m_packetSize = std::numeric_limits<Uint8>::max();
	m_isHost = false;
	m_id = -1;
}

bool Client::connectToServer()
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

void Client::disconnectFromServer()
{
	if (m_connected == true)
	{
		m_connected = false;
		SDLNet_UDP_Close(m_socket);
		m_socket = NULL;
	}
}

void Client::init()
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
				std::cout << "ID: " << m_id << std::endl;
				std::cout << "Seed: " << m_serverSeed << std::endl;
			}
		}
	}
}

void Client::listen()
{
	if (SDLNet_UDP_Recv(m_socket, m_packet) > 0)
	{
		Packet packet;
		packet.append(m_packet->data, m_packet->len);

		Uint8 packetType;
		packet >> packetType;

		//if (packetType >= (Uint8)PacketType::CONNECT && packetType < (Uint8)PacketType::OutOfBounds)
		//{

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
			int id = 0;
			float x = 0;
			float y = 0;

			packet >> id;
			packet >> x;
			packet >> y;

			std::cout << "ID: " << id;
			std::cout << " X: " << x;
			std::cout << " Y: " << y << std::endl;
		}
		//}
	}
}

void Client::send(Packet packet)
{
	if (packet.getDataSize() > 0)
	{
		m_packet->len = packet.getDataSize();
		memcpy(m_packet->data, packet.getData(), m_packet->len);
		SDLNet_UDP_Send(m_socket, -1, m_packet);
	}
}

bool Client::getConnected()
{
	return m_connected;
}

void Client::setHost(bool host)
{
	m_isHost = true;
}

bool Client::getHost()
{
	return m_isHost;
}

int Client::getServerSeed()
{
	return m_serverSeed;
}

int Client::getID()
{
	return m_id;
}

//int Client::getServerTime()
//{
//	return m_serverTimeOffset + SDL_GetTicks();
//}

//void Client::setServerTime(Uint32 serverTime)
//{
//	m_serverTimeOffset = serverTime - SDL_GetTicks();
//}