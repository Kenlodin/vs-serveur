#include <core/network/Packet.hh>

Packet::Packet()
: currentPos_(0)
{
    
}
Packet::Packet(const Packet& orig)
: currentPos_(orig.GetCurrentPos())
{
  std::copy(orig.data_.begin(), orig.data_.end(), data_.begin()); 
  UpdateSize();
}

Packet::~Packet()
{
  UpdateSize();
}

void Packet::Append (const char* data, int size)
{
  std::copy(data, &(data[size]), data_.begin() + currentPos_);
  currentPos_ += size;
  UpdateSize();
}

void Packet::Extract (const char* data, int size)
{
  char* ptr = const_cast<char*>(data);
  std::copy(data_.begin()+currentPos_, data_.begin() + currentPos_ + size, ptr);
  currentPos_ += size;
  UpdateSize();
}

Packet Packet::operator= (const Packet& packet)
{
  return Packet(packet);
}

Packet& operator<<(Packet& packet, const int val)
{
  char* content = (char*)(&val);
  packet.Append(content, 4);
  return packet;
}

Packet& operator<<(Packet& packet, const uint16_t val)
{
  char* content = (char*)(&val);
  packet.Append(content, 2);
  return packet;
}

Packet& operator<<(Packet& packet, const int16_t val)
{
  char* content = (char*)(&val);
  packet.Append(content, 2);
  return packet;
}

Packet& operator<<(Packet& packet, uint8_t val)
{
  char* content = (char*)(&val);
  packet.Append(content, 1);
  return packet;
}

Packet& operator<<(Packet& packet, std::string val)
{
  std::vector<char>& data = packet.GetData();
  packet << (int)val.size();
  packet.Append(val.c_str(), val.size());
  return packet;
  
}

Packet& operator>>(Packet& packet, int& val)
{
  char content[4];
  packet.Extract(content, 4);
  val = *((int*)(content));
  return packet;
}

Packet& operator>>(Packet& packet, uint16_t& val)
{
  char content[2];
  packet.Extract(content, 2);
  val = *((uint16_t*)(content));
  return packet;
}

Packet& operator>>(Packet& packet, int16_t& val)
{
  char content[2];
  packet.Extract(content, 2);
  val = *((int16_t*)(content));
  return packet;
    
}

Packet& operator>>(Packet& packet, uint8_t& val)
{
  char content[1];
  packet.Extract(content, 1);
  val = *((uint8_t*)(content));
  return packet;
    
}

Packet& operator>>(Packet& packet, std::string& val)
{
  char content[4];
  packet.Extract(content, 4);
  int len = *((int*)(content));
  val.resize(len);
  packet.Extract(val.data(), len);
  return packet;
    
}
