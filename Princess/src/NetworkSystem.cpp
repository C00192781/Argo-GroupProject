#include "NetworkSystem.h"

NetworkSystem::NetworkSystem()
{
	m_connected = false;
	m_serverTimeOffset = 0;
	m_serverTimeout = 3000;
	m_packetSize = std::numeric_limits<Uint8>::max();
	m_isHost = false;
	m_id = -1;

	// (connectToServer())
	//
	//nit();
	//rand(getServerSeed());
	//_active = true;
	//
	//f (m_id == 0)
	//
	//m_isHost = true;
	//
	//
	//se
	//
	//rand(time(NULL));
	//_active = false;
	//

	m_maxTimeTilNextPacket = 0.002;
	m_timeTilNextPacket = 0;
}

NetworkSystem::NetworkSystem(EventListener *listener)
{
	m_connected = false;
	m_serverTimeOffset = 0;
	m_serverTimeout = 3000;
	m_packetSize = std::numeric_limits<Uint8>::max();
	m_isHost = false;
	m_id = -1;

	//if (connectToServer())
	//{
	//	init();
	//	srand(getServerSeed());
	//	m_active = true;
	//
	//	if (m_id == 0)
	//	{
	//		m_isHost = true;
	//	}
	//}
	//else
	//{
	//	srand(time(NULL));
	//	m_active = false;
	//}

	m_maxTimeTilNextPacket = 0.002;
	m_timeTilNextPacket = 0;

	m_listener = listener;
	m_listener->host = m_isHost;
	m_listener->connected = m_connected;
}

void NetworkSystem::Update(float deltaTime)
{
	listen();

	if (m_timeTilNextPacket > m_maxTimeTilNextPacket)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			PositionComponent* positionComponent = static_cast<PositionComponent*>(m_entities.at(i)->FindComponent("PC"));
			MovementComponent* movementComponent = static_cast<MovementComponent*>(m_entities.at(i)->FindComponent("movement"));
			ControlComponent* controlComponent = static_cast<ControlComponent*>(m_entities.at(i)->FindComponent("control"));
			NetworkIDComponent* networkIDComponent = static_cast<NetworkIDComponent*>(m_entities.at(i)->FindComponent("network"));

			if (m_entities.at(i)->ID() == "Player" && networkIDComponent->getID() == m_id && movementComponent->getMoving() == true)
			{
				Packet packet;

				packet << (Uint8)PacketType::UPDATEPLAYERS << m_id << positionComponent->getX() << positionComponent->getY();

				send(packet);

				std::cout << positionComponent->getX() << std::endl;
			}

			if (m_isHost == true)
			{
				if (m_listener->ToDungeon1 == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "Dungeon 1";

					send(packet);
					m_listener->ToDungeon1 = false;
				}
				else if (m_listener->ToDungeon2 == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "Dungeon 2";

					send(packet);
					m_listener->ToDungeon2 = false;
				}
				else if (m_listener->ToDungeon3 == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "Dungeon 3";

					send(packet);
					m_listener->ToDungeon3 = false;
				}
				else if (m_listener->ToDungeon4 == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "Dungeon 4";

					send(packet);
					m_listener->ToDungeon4 = false;
				}
				else if (m_listener->ToDungeon5 == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "Dungeon 5";

					send(packet);
					m_listener->ToDungeon5 = false;
				}
				else if (m_listener->ToWorldMap == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "World";

					send(packet);
					m_listener->ToWorldMap = false;
				}
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
			int id = 0;
			float x = 0;
			float y = 0;

			packet >> id;
			packet >> x;
			packet >> y;

			for (int i = 0; i < m_entities.size(); i++)
			{
				if (m_entities.at(i)->ID() == "Player")
				{
					NetworkIDComponent* networkIDComponent = static_cast<NetworkIDComponent*>(m_entities.at(i)->FindComponent("network"));

					if (networkIDComponent->getID() == id)
					{
						CollisionComponent* collisionComponent = static_cast<CollisionComponent*>(m_entities.at(i)->FindComponent("collision"));

						collisionComponent->setX(x);
						collisionComponent->setY(y);
						break;
					}
				}
			}
		}
		else if (packetType == (Uint8)PacketType::UPDATEINSTANCE)
		{
			std::string string;
			packet >> string;

			if (string == "Dungeon 1")
			{
				m_listener->ToDungeon1 = true;
			}
			else if (string == "Dungeon 2")
			{
				m_listener->ToDungeon2 = true;
			}
			else if (string == "Dungeon 3")
			{
				m_listener->ToDungeon3 = true;
			}
			else if (string == "Dungeon 4")
			{
				m_listener->ToDungeon4 = true;
			}
			else if (string == "Dungeon 5")
			{
				m_listener->ToDungeon5 = true;
			}
			else if (string == "World")
			{
				std::cout << "WORLD" << std::endl;
				m_listener->ToWorldMap = true;
			}
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