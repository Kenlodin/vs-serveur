/* 
 * File:   AdminServer.hh
 * Author: aymeric
 *
 * Created on 14 mai 2012, 15:13
 */

#ifndef ADMINSERVER_HH
#define	ADMINSERVER_HH

#include "../Log/Log.hh"
#include "../PacketHandler.hh"
#include "../fwd.hh"
#include "../Tools/Tools.hh"
#include "../Tools/Http/Http.hh"
#include "../Network/ClientList.hh"

class AdminServer : public PacketHandler
{
  /**
   * Constructor & Destructor private parceque Singleton
   */
private:
  AdminServer();
  virtual ~AdminServer();

public:
  static AdminServer& getInstance();

public:
  int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);

private:
  typedef int (AdminServer::*handler)(sf::Packet& packet, sf::SocketTCP& sock);
  const handler route_[AS::MAX_VALUE];

private:
  int send(sf::SocketTCP& sender, sf::Packet& packet);

private:
  int asShutdown(sf::Packet& packet, sf::SocketTCP& sock);
  int asClear(sf::Packet& packet, sf::SocketTCP& sock);
  int asDownloadOrig(sf::Packet& packet, sf::SocketTCP& sock);
  int asDownload(sf::Packet& packet, sf::SocketTCP& sock);
  int asRemove(sf::Packet& packet, sf::SocketTCP& sock);


};

#endif	/* ADMINSERVER_HH */

