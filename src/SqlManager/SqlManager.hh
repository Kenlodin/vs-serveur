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
  void execute (std::string query);
 public:
  static SqlManager* getInstance ();

 private:
  SqlManager () {};
  
 private:
  pqxx::connection* connection_;
} ;

#endif /* SQLMANAGER_HH_ */
