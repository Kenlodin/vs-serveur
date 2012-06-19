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
#include "../SqlManager/SqlManager.hh"
#include "../Tools/ChunkCounter/ChunckCounter.hh"

class AdminServer : public PacketHandler
{
  /**
   * Constructor & Destructor private parceque Singleton
   */
private:
  AdminServer();
  virtual ~AdminServer();

public:
  /**
   * Retourne une unique instance de la classe AdminServer
   * @return 
   */
  static AdminServer& getInstance();

public:
  /**
   * 
   * @param code
   * @param packet
   * @param sock
   * @return 
   */
  int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);

private:
  typedef int (AdminServer::*handler)(sf::Packet& packet, sf::SocketTCP& sock);
  const handler route_[AS::MAX_VALUE];

private:
  /**
   * 
   * @param sender
   * @param packet
   * @return 
   */
  int send(sf::SocketTCP& sender, sf::Packet& packet);

private:
  ///
  /// L'ensemble des méthodes ci-dessous sont de type AdminServeur lui 
  /// demandant d'effectuer une action
  ///
  
  /**
   * Elle coupe donc le serveur (close socket client, ...)
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return Si tout c'est passé correctement
   */
  int asShutdown(sf::Packet& packet, sf::SocketTCP& sock);
  
  /**
   * Suppression de tous les clients connectées au serveur.
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asClear(sf::Packet& packet, sf::SocketTCP& sock);
  
  /**
   * Le serveur va télécharger via le lien d'origine (HTTP) la vidéo. Cette fonction
   * est généralement appellée lors de l'ajout de la vidéo une unique fois sur
   * un seul serveur
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asDownloadOrig(sf::Packet& packet, sf::SocketTCP& sock);
  
  /**
   * Le serveur va télécharger une vidéo sur un autre serveur.
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asDownload(sf::Packet& packet, sf::SocketTCP& sock);
  
  /**
   * Déconnecte un client du serveur.
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asRemove(sf::Packet& packet, sf::SocketTCP& sock);


};

#endif	/* ADMINSERVER_HH */

