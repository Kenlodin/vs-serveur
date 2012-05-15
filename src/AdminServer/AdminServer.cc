/* 
 * File:   AdminServer.cc
 * Author: aymeric
 * 
 * Created on 14 mai 2012, 15:13
 */

#include "AdminServer.hh"

AdminServer::AdminServer () :
route_ ({
        &AdminServer::asShutdown, &AdminServer::asClear,
        &AdminServer::asDownloadOrig, &AdminServer::asDownload,
        &AdminServer::asRemove
})
{
}

AdminServer::~AdminServer ()
{
}

AdminServer&
AdminServer::getInstance ()
{
  static AdminServer instance_;
  return instance_;
}

int
AdminServer::routing (unsigned int code, sf::Packet& packet, sf::SocketTCP& sock)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG ("[AdminServer] routing() code : " + tools::toString<unsigned int> (code));
  sock = sock;
  if (code < AS::MAX_VALUE)
  {
    if ((retVal = (this->*route_[code])(packet, sock)) != RETURN_VALUE_GOOD)
    {
      COUTDEBUG ("[AdminServer] routing () : Error sur la fonction callback");
      if (retVal == RETURN_VALUE_ERROR)
        COUTDEBUG ("\tRETURN_VALUE_ERROR");
      else
        COUTDEBUG ("\tRETURN_VALUE_SUPPRESS");
    }
    return retVal;
  }
  else
  {
    COUTDEBUG ("[AdminServer] routing() : Mauvais OpCode (> à AS::AS_MAX_VALUE");
    ClientList::getInstance ().addBadClient (sock, retVal);
    // Fixme : Envoyer un message au client ?
    return retVal;
  }
}

int
AdminServer::asShutdown (sf::Packet& packet, sf::SocketTCP& sock)
{
  packet = packet;
  sock = sock;
  return 1;
}

int
AdminServer::asClear (sf::Packet& packet, sf::SocketTCP& sock)
{
  packet = packet;
  sock = sock;
  return 1;
}

int
AdminServer::asDownload (sf::Packet& packet, sf::SocketTCP& sock)
{
  packet = packet;
  sock = sock;
  return 1;
  std::string token;
  sf::Int32 video_id, server_id;
  packet >> token >> video_id >> server_id;
  COUTDEBUG("[AdminServer] asDownload ()");
  COUTDEBUG("\t Video_id : " + tools::toString<int> (video_id));
  COUTDEBUG("\t server_id : " + tools::toString<int> (server_id));
  COUTDEBUG("\t Ne fait rien pour le moment. Fixme ...");
  return RETURN_VALUE_GOOD;
}

int
AdminServer::asDownloadOrig (sf::Packet& packet, sf::SocketTCP& sock)
{
  sock = sock;
  std::string token;
  sf::Int32 video_id;
  std::string url;
  packet >> token >> video_id >> url;
  COUTDEBUG("[AdminServer] asDownloadOrig : ");
  COUTDEBUG("\t video_id : " + tools::toString<sf::Int32> (video_id));
  COUTDEBUG("\t url : " + url);
  if (tools::Http::download (url, "movie/" + tools::toString<int> (video_id) + ".avi") == 0)
    return RETURN_VALUE_GOOD;
  else
  {
    COUTDEBUG("\t Impossible de télécharger la vidéo ...");
    return RETURN_VALUE_ERROR;
  }
}

int
AdminServer::asRemove (sf::Packet& packet, sf::SocketTCP& sock)
{
  packet = packet;
  sock = sock;
  return 1;
}

int 
AdminServer::send(sf::SocketTCP& sender, sf::Packet& packet)
{
  if (sender.Send(packet) == sf::Socket::Done)
    return RETURN_VALUE_GOOD;
  return RETURN_VALUE_ERROR;
}
