/*
 * VodClient.hxx
 *
 *  Created on: 9 mai 2012
 *      Author: nagriar
 */

#ifndef VODCLIENT_HXX_
# define VODCLIENT_HXX_

//Internal include
# include "VodClient.hh"

inline
Chunk* VodClient::getElement(int number)
{
  return getFileVideo()->getPacket(number);
}

#endif /* VODCLIENT_HXX_ */
