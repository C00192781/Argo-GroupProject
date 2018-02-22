#include "Packet.h"

Packet::Packet()
{
	m_readPos = 0;
}

void Packet::clear()
{
	m_data.clear();
	m_readPos = 0;
}

void Packet::append(const void* newData, std::size_t size)
{
	// if there is new data to copy into data
	if (newData != NULL && size > 0)
	{
		std::size_t start = m_data.size();
		m_data.resize(start + size);
		memcpy(&m_data.at(start), newData, size); // copies number of bytes from newData into data
	}
}

char* Packet::getData()
{
	return &m_data.at(0);
}

std::size_t Packet::getDataSize()
{
	return m_data.size();
}

bool Packet::checkSize(std::size_t size)
{
	if (m_readPos + size <= m_data.size()) // < instead of <= maybe?
	{
		return true;
	}
	else
	{
		return false;
	}
}

Packet& Packet::operator >> (Uint8 &data)
{
	if (checkSize(sizeof(data)) == true)
	{
		data = *reinterpret_cast<const Uint8*>(&m_data.at(m_readPos));
		m_readPos += sizeof(data);
	}
	return *this; // return reference to this packet of data
}

Packet& Packet::operator >> (Uint16 &data)
{
	if (checkSize(sizeof(data)) == true)
	{
		data = *reinterpret_cast<const Uint16*>(&m_data.at(m_readPos));
		m_readPos += sizeof(data);
	}
	return *this; // return reference to this packet of data
}

Packet& Packet::operator >> (Uint32 &data)
{
	if (checkSize(sizeof(data)) == true)
	{
		data = *reinterpret_cast<const Uint32*>(&m_data.at(m_readPos));
		m_readPos += sizeof(data);
	}
	return *this; // return reference to this packet of data
}

Packet& Packet::operator >> (int &data)
{
	if (checkSize(sizeof(data)) == true)
	{
		data = *reinterpret_cast<const int*>(&m_data.at(m_readPos));
		m_readPos += sizeof(data);
	}
	return *this; // return reference to this packet of data
}

Packet& Packet::operator >> (float &data)
{
	if (checkSize(sizeof(data)) == true)
	{
		data = *reinterpret_cast<const float*>(&m_data.at(m_readPos));
		m_readPos += sizeof(data);
	}
	return *this; // return reference to this packet of data
}

Packet& Packet::operator >> (double &data)
{
	if (checkSize(sizeof(data)) == true)
	{
		data = *reinterpret_cast<const double*>(&m_data.at(m_readPos));
		m_readPos += sizeof(data);
	}
	return *this; // return reference to this packet of data
}

Packet& Packet::operator >> (std::string &data)
{
	Uint32 length = data.size();
	*this >> length;

	data.clear();

	if (length > 0 && checkSize(length) == true)
	{
		data.assign(&m_data.at(m_readPos), length);
		m_readPos += length;
	}

	return *this; // return reference to this packet of data
}

Packet& Packet::operator << (Uint8 data)
{
	append(&data, sizeof(data));
	return *this;
}

Packet& Packet::operator << (Uint16 data)
{
	append(&data, sizeof(data));
	return *this;
}

Packet& Packet::operator << (Uint32 data)
{
	append(&data, sizeof(data));
	return *this;
}

Packet& Packet::operator << (int data)
{
	append(&data, sizeof(data));
	return *this;
}

Packet& Packet::operator << (float data)
{
	append(&data, sizeof(data));
	return *this;
}

Packet& Packet::operator << (double data)
{
	append(&data, sizeof(data));
	return *this;
}

Packet& Packet::operator << (std::string data)
{
	Uint32 length = static_cast<Uint32>(data.size());
	*this << length;

	if (length > 0)
	{
		append(data.c_str(), length * sizeof(std::string::value_type));
	}
	return *this;
}