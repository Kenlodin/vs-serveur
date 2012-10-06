#ifndef PACKET_HXX
# define PACKET_HXX

#include <core/network/Packet.hh>

inline
uint Packet::GetDataSize()
{
  return data.size();
}

inline
void Packet::SetDataSize(uint dataSize)
{
  data.resize(dataSize);  
}

inline
bool Packet::EndOfPacket()
{
  return currentPos_ == data.size();    
}

inline
std::vector<char>& Packet::GetData()
{
    return data;
}

#endif /* PACKET_HXX */
