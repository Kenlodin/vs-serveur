/* 
 * File:   Packet.hh
 * Author: nagriar
 *
 * Created on 23 septembre 2012, 00:39
 */

#ifndef PACKET_HH
#define	PACKET_HH

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
    void* GetData();
    
    void* data;
private:

};

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

