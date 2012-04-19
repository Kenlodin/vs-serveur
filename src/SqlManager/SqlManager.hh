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


typedef std::vector<std::map<std::string, std::string> > sql_result;

/**
 * Cette classe permet de discuter avec la base de données. Elle utilise la 
 * bibliothèque libpqxx.
 */
class SqlManager
{
  typedef std::map<std::string, std::string> map;
  typedef std::pair<std::string, std::string> pair;
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
  sql_result getThreeServers ();
 public:
  static SqlManager& getInstance ();

 private:
  SqlManager () {};
  
 private:
  pqxx::connection* connection_;
} ;

#endif /* SQLMANAGER_HH_ */
