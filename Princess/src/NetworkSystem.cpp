#include "NetworkSystem.h"

NetworkSystem::NetworkSystem()
{
	m_connected = false;
	m_serverTimeOffset = 0;
	m_serverTimeout = 3000;
	m_packetSize = std::numeric_limits<Uint8>::max();
	m_isHost = false;
	m_id = -1;

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
			WeaponComponent* weaponComponent = static_cast<WeaponComponent*>(m_entities.at(i)->FindComponent("weapon"));
			AttributesComponent* attributeComponent = static_cast<AttributesComponent*>(m_entities.at(i)->FindComponent("attribute"));

			if (m_entities.at(i)->ID() == "Player" && networkIDComponent->getID() == m_id && movementComponent->getMoving() == true)
			{
				Packet packet;

				packet << (Uint8)PacketType::UPDATEPLAYERS << m_id << positionComponent->getX() << positionComponent->getY();

				send(packet);
			}

			if (m_listener->ChangedWeapon == true)
			{
				Packet packet;

				packet << (Uint8)PacketType::UPDATEWEAPON << m_id << (int)weaponComponent->getWeaponType() << weaponComponent->getDamage() << weaponComponent->getRange() << weaponComponent->getAttackSpeed();

				send(packet);
 
				m_listener->ChangedWeapon = false;
			}

			if (m_listener->ChangedArmor == true)
			{
				Packet packet;

				packet << (Uint8)PacketType::UPDATEATTRIBUTES << m_id << attributeComponent->AdditiveHealth() << attributeComponent->AdditiveArmour();

				send(packet);

				m_listener->ChangedArmor = false;
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
				else if (m_listener->ToTown == true)
				{
					Packet packet;

					packet << (Uint8)PacketType::UPDATEINSTANCE << "Town";

					send(packet);
					m_listener->ToTown = false;
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
				m_listener->ToWorldMap = true;
			}
			else if (string == "Town")
			{
				m_listener->ToTown = true;
			}
		}
		else if (packetType == (Uint8)PacketType::UPDATEWEAPON)
		{
			int id;
			int type;
			int damage;
			int range;
			int attackSpeed;

			packet >> id;
			packet >> type;
			packet >> damage;
			packet >> range;
			packet >> attackSpeed;

			for (int i = 0; i < m_entities.size(); i++)
			{
				if (m_entities.at(i)->ID() == "Player")
				{
					NetworkIDComponent* networkIDComponent = static_cast<NetworkIDComponent*>(m_entities.at(i)->FindComponent("network"));

					if (networkIDComponent->getID() == id)
					{
						WeaponComponent* weaponComponent = static_cast<WeaponComponent*>(m_entities.at(i)->FindComponent("weapon"));

						if (type == 0)
						{
							weaponComponent->setWeaponType(WeaponType::MELEE);
						}
						else if (type == 1)
						{
							weaponComponent->setWeaponType(WeaponType::RANGE);
						}
						else
						{
							weaponComponent->setWeaponType(WeaponType::STAFF);
						}

						weaponComponent->setDamage(damage);
						weaponComponent->setRange(range);
						weaponComponent->setAttackSpeed(attackSpeed);

						break;
					}
				}
			}
		}
		else if (packetType == (Uint8)PacketType::UPDATEATTRIBUTES)
		{
			int id;
			int health;
			int armour;

			packet >> id;
			packet >> health;
			packet >> armour;

			for (int i = 0; i < m_entities.size(); i++)
			{
				if (m_entities.at(i)->ID() == "Player")
				{
					NetworkIDComponent* networkIDComponent = static_cast<NetworkIDComponent*>(m_entities.at(i)->FindComponent("network"));

					if (networkIDComponent->getID() == id)
					{
						AttributesComponent* attributeComponent = static_cast<AttributesComponent*>(m_entities.at(i)->FindComponent("attribute"));

						attributeComponent->AdditiveHealth(health);
						attributeComponent->AdditiveArmour(armour);

						std::cout << "OKAY WE RECEIVED IT" << std::endl;

						break;
					}
				}
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