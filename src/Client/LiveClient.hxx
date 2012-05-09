/*
 * LiveClient.hxx
 *
 *  Created on: 9 mai 2012
 *      Author: nagriar
 */

#ifndef LIVECLIENT_HXX_
# define LIVECLIENT_HXX_

// Internal include
# include "LiveClient.hh"

inline
Chunk* LiveClient::getElement(int number)
{
  return getFileVideo()->getPacket(number);
}

#endif /* LIVECLIENT_HXX_ */
