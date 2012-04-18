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
    Chuck();
    Chuck(int length, sf::Int8* data);
    virtual ~Chuck();
    sf::Int8* getData() const;
    void setData(sf::Int8* data);
    int getLength() const;
    void setLength(int length);
  private:
    int length_;
    sf::Int8* data_;
};

#endif /* CHUCK_HH_ */
