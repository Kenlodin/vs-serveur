/* 
 * File:   Packet.hh
 * Author: nagriar
 *
 * Created on 23 septembre 2012, 00:39
 */

#ifndef PACKET_HH
#define	PACKET_HH

//intenal include
# include <core/fwd.hh>

//external include
# include <string>
#include <stdint.h>

class Packet {
public:
    Packet();
    Packet(const Packet& orig);
    virtual ~Packet();
    void Append (void* data, int size);
    bool EndOfPacket();
    uint GetDataSize();
    void SetDataSize(uint dataSize);
    std::vector<char>& GetData();
    const int headerSize = 4; //size of int
    Packet& operator= (const Packet& packet);
private:
    std::vector<char> data;
    uint currentPos_;
    
};

#include <core/network/Packet.hxx>

Packet& operator<<(Packet& packet, int val);
Packet& operator<<(Packet& packet, uint16_t val);
Packet& operator<<(Packet& packet, int16_t val);
Packet& operator<<(Packet& packet, uint8_t val);
Packet& operator<<(Packet& packet, std::string val);

Packet& operator>>(Packet& packet, int val);
Packet& operator>>(Packet& packet, uint16_t val);
Packet& operator>>(Packet& packet, int16_t val);
Packet& operator>>(Packet& packet, uint8_t val);
Packet& operator>>(Packet& packet, std::string val);

#endif	/* PACKET_HH */

