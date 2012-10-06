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
    void Append (const char* const data, int size);
    void Extract (const char* data, int size);
    bool EndOfPacket() const;
    uint GetDataSize() const;
    uint GetCurrentPos() const;
    void SetCurrentPos(uint dataPos);
    std::vector<char>& GetData();
    const int headerSize = 4; //size of int
    Packet operator= (const Packet& packet);
private:
    void UpdateSize();
    std::vector<char> data_;
    uint currentPos_;
    
};

#include <core/network/Packet.hxx>

Packet& operator<<(Packet& packet, const int val);
Packet& operator<<(Packet& packet, const uint16_t val);
Packet& operator<<(Packet& packet, const int16_t val);
Packet& operator<<(Packet& packet, const uint8_t val);
Packet& operator<<(Packet& packet, const std::string val);

Packet& operator>>(Packet& packet, int& val);
Packet& operator>>(Packet& packet, uint16_t& val);
Packet& operator>>(Packet& packet, int16_t& val);
Packet& operator>>(Packet& packet, uint8_t& val);
Packet& operator>>(Packet& packet, std::string& val);

#endif	/* PACKET_HH */

