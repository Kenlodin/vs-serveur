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
# include <boost/thread/mutex.hpp>
#include "../Tools/Tools.hh"
#include "../Log/Log.hh"
#include "../Config/Config.hh"

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
  void addServer (std::string ip, int port);
  std::string addClient (std::string login, std::string password,
                        std::string public_ip, std::string private_ip,
                        int bandwith);

  sql_result saveClientServerConnection (std::string client_token, int server_id);
  sql_result setHandlings (std::string client_token, int file_id);
  sql_result setFileServer (int file_id);
  
  
 public:
  sql_result getThreeServers ();
  sql_result getAllFlux ();
  sql_result getFlux (int id);
  sql_result getNextsHandlings (int server_id);

 public:
  static SqlManager&
  getInstance ();

 private:

  SqlManager () { };

 private:
  pqxx::connection* connection_;
  boost::mutex mutex_;
} ;

#endif /* SQLMANAGER_HH_ */
