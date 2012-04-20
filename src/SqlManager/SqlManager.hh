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
#include "../Tools/Tools.hh"


typedef pqxx::result sql_result;
typedef pqxx::result::tuple sql_tuple;

/**
 * Cette classe permet de discuter avec la base de données. Elle utilise la 
 * bibliothèque libpqxx.
 */
class SqlManager
{
 public:
  /**
   * Permet de se connecter à la base de données.
   */
  void connect ();

  /**
   * Permet d'exécuter une requête SQL
   * @param query La requête SQL
   */
  pqxx::result execute (std::string query);

 public:
  sql_result addServer (std::string ip, int port);
  sql_result saveClientServerConnection (int client_id, int server_id);
  
 public:
  sql_result getThreeServers ();
  sql_result getAllFlux ();
  sql_result getFile (int id);
 public:
  static SqlManager& getInstance ();

 private:

  SqlManager () { };

 private:
  pqxx::connection* connection_;
} ;

#endif /* SQLMANAGER_HH_ */
