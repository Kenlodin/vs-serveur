/*
 * Chuck.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CHUNCK_HH_
# define CHUNCK_HH_

//External include
# include <SFML/System.hpp>

// Internal include
# include "../fwd.hh"

/*
 * Class which represent a chuck of avi
 */
class Chunk
{
  public:
    // Constructor
    Chunk();

    // Destructor
    virtual ~Chunk();

    // Empting the chunck
    void clear();
  public:
    avifile::s_sub_chunk *subChunk_;
};

#endif /* CHUNCK_HH_ */
