/*
 * Chuck.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CHUCK_HH_
#define CHUCK_HH_

# include <SFML/System.hpp>
# include "../fwd.hh"

class Chuck
{
  public:
    Chuck();
    virtual ~Chuck();
    void clear();
  public:
    avifile::s_sub_chunk *subChunk_;
};

#endif /* CHUCK_HH_ */
