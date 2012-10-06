#ifndef PACKET_HXX
# define PACKET_HXX

#include <core/network/Packet.hh>

inline
uint Packet::GetDataSize() const
{
  return data_.size() - 4;
}

inline
void Packet::UpdateSize()
{
  uint size = GetDataSize();
  data_[0] = size >> 12;
  data_[1] = (size >> 8) & 0xff;
  data_[2] = (size >> 4) & 0xff;
  data_[3] = size & 0xff;
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
