/* 
 * File:   AdminServer.hh
 * Author: aymeric
 *
 * Created on 14 mai 2012, 15:13
 */

#ifndef ADMINSERVER_HH
#define	ADMINSERVER_HH

#include <core/log/Log.hh>
#include <core/PacketHandler.hh>
#include <core/fwd.hh>
#include <core/tools/Tools.hh>
#include <core/tools/http/Http.hh>
#include <core/network/ClientList.hh>
#include <core/sqlManager/SqlManager.hh>
#include <core/tools/chunkCounter/ChunckCounter.hh>

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
  int routing(unsigned int code, Packet& packet, Client*& client);

private:
  typedef int (AdminServer::*handler)(Packet& packet, Client*& client);
  const handler route_[AS::MAX_VALUE];

private:
  /**
   * 
   * @param sender
   * @param packet
   * @return 
   */
  int send(Client*& sender, Packet& packet);

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
  int asShutdown(Packet& packet, Client*& client);
  
  /**
   * Suppression de tous les clients connectées au serveur.
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asClear(Packet& packet, Client*& client);
  
  /**
   * Le serveur va télécharger via le lien d'origine (HTTP) la vidéo. Cette fonction
   * est généralement appellée lors de l'ajout de la vidéo une unique fois sur
   * un seul serveur
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asDownloadOrig(Packet& packet, Client*& client);
  
  /**
   * Le serveur va télécharger une vidéo sur un autre serveur.
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asDownload(Packet& packet, Client*& client);
  
  /**
   * Déconnecte un client du serveur.
   * 
   * @param packet Le packet reçus
   * @param sock Le socket
   * @return 
   */
  int asRemove(Packet& packet, Client*& client);


};

#endif	/* ADMINSERVER_HH */

