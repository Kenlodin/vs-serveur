/*
 * SqlManager.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef SQLMANAGER_HH_
#define SQLMANAGER_HH_

#include <pqxx/pqxx>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <core/tools/Tools.hh>
#include <core/log/Log.hh>
#include <core/config/Config.hh>

typedef pqxx::result sql_result;
typedef pqxx::result::tuple sql_tuple;

/**
 * Cette classe permet de discuter avec la base de données. Elle utilise la 
 * bibliothèque libpqxx.
 */
class SqlManager
{
 public:
  /**)
   * Permet de se connecter à la base de données.
   */
  void connect ();

  /**
   * Permet d'exécuter une requête SQL
   * @param query La requête SQL
   */
  pqxx::result execute (std::string query);

 public:
   /**
    * Ajoute un serveur à la base de données
    * 
    * @param ip L'ip du serveur
    * @param port Le port utilisé par le socket de diffusion
    */
  void addServer (std::string ip, int port);
  
  /**
   * Ajoute un client à la base de données avec toutes les informations
   * de celui-ci.
   * Cette vérifie d'abord que les identifiants (login et password) sont
   * correctes.
   * 
   * @param login Le login de connexion
   * @param password Le mot de passe de connexion
   * @param public_ip L'adresse ip internet du client
   * @param private_ip L'adresse ip local du client
   * @param bandwith La bande passante du client
   * @return Le token du client
   */
  std::string addClient (std::string login, std::string password,
                         std::string public_ip, std::string private_ip,
                         int bandwith);

  /**
   * Ajoute dans la base de données la connexion entre le client et le serveur
   * 
   * @param client_token Le token du client
   * @param server_id L'id du serveur.
   * @return 
   */
  sql_result saveClientServerConnection (std::string client_token, int server_id);
  
  /**
   * Ajoute les traitements à effectuer pour le client dans la base de données
   * Cette fonction est appellée quand le client demande au serveur le visionnage
   * d'un flux.
   * 
   * @param client_token Le token du client
   * @param file_id L'id du fichier que le client veut visionner
   */
  void setHandlings (std::string client_token, int file_id);
  
  /**
   * Ajoute dans la base de données la relation entre un fichier et un serveur.
   * Il faut appeller cette fonction pour toutes les vidéos que le serveur a 
   * dans le dossier "movie"
   * 
   * @param file_id L'id du fichier 
   * @return 
   */
  sql_result setFileServer (std::string file_id);
  
  /**
   * C'est une surcharge de la fonction précédente. En faite elle va convertir
   * file_id en string et appellé la fonction précédente.
   * 
   * @param file_id L'id du fichier 
   * @return 
   */
  sql_result setFileServer (int file_id);
 
  /**
   * Met à jour dans la base de données les informations d'une vidéo (taille, ...)
   *
   * @param id Id du fichier
   * @param size Taille du fichier
   * @param length Durée de la vidéo
   * @param nb_packet nombre de chunk
   */
  void updateFileInfos(int id, int size, int length, int nb_packet);

 public:
   /**
    * Récupère la liste des trois serveurs les plus intéressants pour le client
    * 
    * @return La liste des trois serveurs
    */
  sql_result getThreeServers ();
  
  /**
   * Retourne la liste des flux disponibles
   * 
   * @return La liste des flux
   */
  sql_result getAllFlux ();
  
  /**
   * Retourne les informations d'un flux en particulier
   * 
   * @param id Id du flux
   * @return Les infos du flux
   */
  sql_result getFlux (int id);
  
  /**
   * Récupère le prochain traitement que le serveur doit effectuer.
   * Un traitement correspond à l'envoie d'un certain nombre de chunk au client
   * 
   * @param server_id L'id du serveur
   * @return Le traitement a effectuer
   */
  sql_result getNextsHandlings (int server_id);
  
  /**
   * Retourne un serveur ayant le fichier video_id.
   * 
   * @param video_id
   * @return 
   */
  sql_result getServerForDD (int video_id);

 public:
   /**
    * Supprime le serveur de la base de données.
    * 
    * @param server_id L'id du serveur
    */
  void disconnectServer (int server_id);
  
  /**
   * Supprime toutes les informations liées à un client (les connexions client/server)
   * les traitements ...
   * 
   * @param token Le token du client
   */
  void disconnectClient (std::string token);
  
  /**
   * Supprime de la base de données la connexion entre le client et le serveur.
   * Cette fonction doit-être appellée lorsque qu'un client se déconnecte d'un
   * serveur
   * 
   * @param client_token Le token du client
   * @param server_id L'id du serveur
   */
  void removeClientServerConnection (std::string client_token, int server_id);

  void deleteHandlings (std::string token);

 public:
  static SqlManager&
  
  /**
   * Retourne une unique instance de la classe SqlManager
   * 
   * @return L'unique instance
   */
  getInstance ();

 private:
   /**
    * Constructor. Private
    */
  SqlManager () { };

 private:
  pqxx::connection* connection_;
  boost::mutex mutex_;
} ;

#endif /* SQLMANAGER_HH_ */
