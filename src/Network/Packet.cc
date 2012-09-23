#include <core/network/Packet.hh>

Packet::Packet()
{
    
}
Packet::Packet(const Packet& orig)
{
    
}

Packet::~Packet()
{
    
}

void Packet::Append (void* data, int size)
{
    
}

bool Packet::EndOfPacket()
{
    
}

uint Packet::GetDataSize()
{
    
}

void* Packet::GetData()
{
    
}

Packet& operator<<(Packet& packet, int val)
{
    
}

Packet& operator<<(Packet& packet, uint16_t val)
{
    
}

Packet& operator<<(Packet& packet, int16_t val)
{
    
}

Packet& operator<<(Packet& packet, uint8_t val)
{
    
}

Packet& operator<<(Packet& packet, std::string val)
{
    
}

Packet& operator>>(Packet& packet, int val)
{
    
}

Packet& operator>>(Packet& packet, uint16_t val)
{
    
}

Packet& operator>>(Packet& packet, int16_t val)
{
    
}

Packet& operator>>(Packet& packet, uint8_t val)
{
    
}

Packet& operator>>(Packet& packet, std::string val)
{
    
}