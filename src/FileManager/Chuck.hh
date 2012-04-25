/*
 * Chuck.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CHUCK_HH_
#define CHUCK_HH_

# include <SFML/System.hpp>

class Chuck
{
  public:
    typedef unsigned long long u64;
    typedef unsigned int u32;
    typedef unsigned short u16;
    typedef unsigned char u8;
    typedef struct
    {
        char fcc[4];
        u32 size;
        void *data;
    }__attribute__((packed)) s_sub_chunk;

  public:
    Chuck();
    virtual ~Chuck();
    void clear();
  public:
    s_sub_chunk *subChunk_;
};

#endif /* CHUCK_HH_ */
