#ifndef PACKET_HXX
# define PACKET_HXX

#include <core/network/Packet.hh>

inline
uint Packet::GetDataSize() const
{
  return data_.size();
}

inline
uint Packet::GetCurrentPos() const
{
  return currentPos_;
}

inline
void Packet::SetCurrentPos(uint dataPos)
{
  currentPos_ = dataPos;
}

inline
bool Packet::EndOfPacket() const
{
  return currentPos_ == data_.size();    
}

inline
std::vector<char>& Packet::GetData()
{
    return data_;
}

#endif /* PACKET_HXX */
