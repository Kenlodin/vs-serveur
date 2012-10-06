/* 
 * File:   AdminServer.cc
 * Author: aymeric
 * 
 * Created on 14 mai 2012, 15:13
 */

#include <core/adminServer/AdminServer.hh>

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
AdminServer::routing (unsigned int code, Packet& packet, Client*& client)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG ("[AdminServer] routing() code : " + tools::toString<unsigned int> (code));
  if (code < AS::MAX_VALUE)
  {
    if ((retVal = (this->*route_[code])(packet, client)) != RETURN_VALUE_GOOD)
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
    ClientList::getInstance ().addBadClient (client, retVal);
    // Fixme : Envoyer un message au client ?
    return retVal;
  }
}

int
AdminServer::asShutdown (Packet& packet, Client*& client)
{
  packet = packet;
  client = client;
  Config::getInstance ().setIsOnline (false);
  ClientList::getInstance ().disconnectAllClient ();
  return RETURN_VALUE_GOOD;
}

int
AdminServer::asClear (Packet& packet, Client*& client)
{
  packet = packet;
  client = client;
  ClientList::getInstance ().disconnectAllClient ();
  return RETURN_VALUE_GOOD;
}

int
AdminServer::asDownload (Packet& packet, Client*& client)
{
  packet = packet;
  client = client;
  return 1;
  std::string token;
  int video_id, server_id;
  packet >> token >> video_id >> server_id;
  COUTDEBUG("[AdminServer] asDownload ()");
  COUTDEBUG("\t Video_id : " + tools::toString<int> (video_id));
  COUTDEBUG("\t server_id : " + tools::toString<int> (server_id));
  COUTDEBUG("\t Ne fait rien pour le moment. Fixme ...");
  return RETURN_VALUE_GOOD;
}

int
AdminServer::asDownloadOrig (Packet& packet, Client*& client)
{
    client = client;
  std::string token;
  int video_id;
  std::string url;
  std::string file;
  
  packet >> token >> video_id >> url;
  file =  "movie/" + tools::toString<int> (video_id) + ".avi";
  
  COUTDEBUG("[AdminServer] asDownloadOrig : ");
  COUTDEBUG("\t video_id : " + tools::toString<int> (video_id));
  COUTDEBUG("\t url : " + url);
  
  if (tools::Http::download (url, file) == 0)
  {
    SqlManager::getInstance ().setFileServer (video_id);
    struct tools::ChunckCounter::result r = tools::ChunckCounter::avi (file);
    SqlManager::getInstance ().updateFileInfos (video_id, r.size, r.length, r.nb_packet);
    COUTDEBUG("\t Téléchargement de la vidéo terminée !");
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("\t Impossible de télécharger la vidéo ...");
    return RETURN_VALUE_ERROR;
  }
}

int
AdminServer::asRemove (Packet& packet, Client*& client)
{
  packet = packet;
  client = client;
  return RETURN_VALUE_ERROR;
}

int 
AdminServer::send(Client*& sender, Packet& packet)
{
  return sender->send(packet);
}
