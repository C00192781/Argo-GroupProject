#include "Server.h"

Server::Server()
{
	m_running = false;
	m_nextClientID = 0;
	///m_totalDataSent(0);
	///m_totalDataReceived(0);
	m_packetSize = std::numeric_limits<Uint8>::max();
	//m_rooms(MAX_ROOMS);
	//m_gameStarted(MAX_ROOMS, false);
	
	srand(time(NULL));
	m_seed = rand();
}

void Server::update()
{
	m_uptime = SDL_GetTicks();

	// times out clients that have lost connection to the server
	for (std::map<int, ClientInfo>::iterator client = m_clients.begin(); client != m_clients.end();)
	{
		Uint32 elapsedTime = m_uptime - (*client).second.m_lastConnectionTime;

		if (elapsedTime > 1000)
		{
			if (elapsedTime > 10000 || (*client).second.m_connectionRetry > 5) // put this back in when yelo loogee stops doing a bad
			{
				client = m_clients.erase(client);
				continue;
			}

			if ((*client).second.m_connectionWaiting == false || (elapsedTime >= 1000 * ((*client).second.m_connectionRetry + 1)))
			{
				Packet packet;
				packet << (Uint8)PacketType::CONNECTIONALIVE << m_uptime;
				send((*client).first, packet);
				if ((*client).second.m_connectionRetry == 0)
				{
					(*client).second.m_currentConnectionTime = m_uptime;
				}
				(*client).second.m_connectionWaiting = true;
				(*client).second.m_connectionRetry++;
				m_totalDataSent += packet.getDataSize();

			}
		}
		++client;
	}

	listen();
}

bool Server::send(const int &id, Packet packet)
{
	std::map<int, ClientInfo>::iterator client = m_clients.find(id);

	if (client != m_clients.end())
	{
		int packetSize = packet.getDataSize();

		if (packetSize > 0)
		{
			m_packet->len = packetSize;
			m_packet->address.host = (*client).second.m_clientIP;
			m_packet->address.port = (*client).second.m_clientPort;
			memcpy(m_packet->data, packet.getData(), m_packet->len);
			SDLNet_UDP_Send(m_socket, -1, m_packet);
			m_totalDataSent += packetSize;
			return true;
		}
	}

	return false;
}

void Server::sendToAll(Packet packet)
{
	for (std::map<int, ClientInfo>::iterator client = m_clients.begin(); client != m_clients.end(); ++client)
	{
		int packetSize = packet.getDataSize();

		if (packetSize > 0)
		{
			m_packet->len = packetSize;
			m_packet->address.host = client->second.m_clientIP;
			m_packet->address.port = client->second.m_clientPort;
			memcpy(m_packet->data, packet.getData(), m_packet->len);
			SDLNet_UDP_Send(m_socket, -1, m_packet);
			m_totalDataSent += m_packetSize;
		}
	}
}

void Server::sendToOtherClients(Packet packet, int id)
{
	for (std::map<int, ClientInfo>::iterator client = m_clients.begin(); client != m_clients.end(); ++client)
	{
		if ((*client).first != id)
		{
			int packetSize = packet.getDataSize();

			if (packetSize > 0)
			{
				m_packet->len = packetSize;
				m_packet->address.host = client->second.m_clientIP;
				m_packet->address.port = client->second.m_clientPort;
				memcpy(m_packet->data, packet.getData(), m_packet->len);
				SDLNet_UDP_Send(m_socket, -1, m_packet);
				m_totalDataSent += m_packetSize;
			}
		}
	}
}

void Server::listen()
{
	int i = 0;
	if (SDLNet_UDP_Recv(m_socket, m_packet) > 0)
	{
		Packet packet;
		packet.append(m_packet->data, m_packet->len);
		m_totalDataReceived += packet.getDataSize();

		Uint8 packetType;
		packet >> packetType;

		// check if connectiong is alive
		if (packetType == (Uint8)PacketType::CONNECTIONALIVE)
		{
			for (std::map<int, ClientInfo>::iterator client = m_clients.begin(); client != m_clients.end(); ++client)
			{
				i++;
				if ((*client).second.m_clientIP == m_packet->address.host && (*client).second.m_clientPort == m_packet->address.port)
				{
					(*client).second.m_ping = m_uptime - (*client).second.m_currentConnectionTime;
					(*client).second.m_lastConnectionTime = m_uptime;
					(*client).second.m_connectionWaiting = false;
					(*client).second.m_connectionRetry = 0;
					break;
				}
			}
		}
		else
		{
			handlePacket(m_packet->address.host, m_packet->address.port, packetType, packet);
		}
	}
}

int Server::addClient(Uint32 & ip, Uint16 & port)
{
	for (std::map<int, ClientInfo>::iterator client = m_clients.begin(); client != m_clients.end(); ++client)
	{
		if ((*client).second.m_clientIP == ip && (*client).second.m_clientPort == port)
		{
			return -1; // stops same client from being added again
		}
	}

	int id = m_nextClientID;
	m_clients.emplace(id, ClientInfo(ip, port, m_uptime));
	m_nextClientID++;

	return id;
}

bool Server::removeClient(int id)
{
	std::map<int, ClientInfo>::iterator client = m_clients.find(id);

	if (client != m_clients.end())
	{
		Packet packet;
		packet << (Uint8)PacketType::DISCONNECT;
		send(id, packet);
		std::cout << (*client).second.m_clientIP << ":" << (*client).second.m_clientPort << " has disconnected." << std::endl;
		m_clients.erase(client);
		return true;
	}

	return false;
}

int Server::getID(const Uint32 & ip, const Uint16 & port)
{
	for (std::map<int, ClientInfo>::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter)
	{
		if ((*iter).second.m_clientIP == ip && (*iter).second.m_clientPort == port)
		{
			return (*iter).first;
		}
	}
	return -1;
}

void Server::disconnectAllClients()
{
	Packet packet;
	packet << (Uint8)PacketType::DISCONNECT;
	sendToAll(packet);
	m_clients.clear();
}

bool Server::start()
{
	if (SDLNet_Init() != -1)
	{
		m_socket = SDLNet_UDP_Open(m_serverPort);
		m_packet = SDLNet_AllocPacket(m_packetSize);
		m_running = true;
		return true;
	}
	return false;
}

bool Server::stop()
{
	disconnectAllClients();
	m_running = false;
	SDLNet_UDP_Close(m_socket);
	m_socket = NULL;
	return true;
}

bool Server::getRunning()
{
	return m_running;
}

void Server::handlePacket(Uint32 &ip, Uint16 &port, Uint8 &packetType, Packet &packet)
{
	int id = getID(ip, port);

	if (packetType == (Uint8)PacketType::CONNECT)
	{
		if (m_clients.size() < m_maxNumberOfClients)
		{
			addClient(ip, port);
		}
	}
	else if (id >= 0)
	{
		if (packetType == (Uint8)PacketType::DISCONNECT)
		{
			removeClient(id);
		}
		else if (packetType == (Uint8)PacketType::UPDATEPLAYERS || packetType == (Uint8)PacketType::UPDATEINSTANCE || packetType == (Uint8)PacketType::UPDATEWEAPON || packetType == (Uint8)PacketType::UPDATEATTRIBUTES)
		{
			sendToOtherClients(packet, id);
		}
		else if (packetType == (Uint8)PacketType::INIT)
		{
			Packet newPacket;

			newPacket << (Uint8)PacketType::INIT << id << m_seed;

			send(id, newPacket);
		}
	}
}