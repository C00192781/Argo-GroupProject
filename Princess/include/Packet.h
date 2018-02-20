#pragma once

#include <SDL.h>
#include <vector>
#include "PacketType.h"

class Packet
{
public:
	Packet();
	~Packet() {};

	void clear();
	void append(const void* data, std::size_t size);
	char* getData();
	std::size_t getDataSize();

	// operators to read from data
	Packet& operator >> (Uint8 &data);
	Packet& operator >> (Uint16 &data);
	Packet& operator >> (Uint32 &data);
	Packet& operator >> (std::string &data);
	Packet& operator >> (int &data);
	Packet& operator >> (float &data);
	Packet& operator >> (double &data);

	// operators to append different types of data to m_data
	Packet& operator << (Uint8 data);
	Packet& operator << (Uint16 data);
	Packet& operator << (Uint32 data);
	Packet& operator << (std::string data);
	Packet& operator << (int data);
	Packet& operator << (float data);
	Packet& operator << (double data);

private:
	std::vector<char> m_data;
	std::size_t m_readPos; // ???
	bool checkSize(std::size_t size); // ????????
};