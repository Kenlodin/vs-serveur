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

class SqlManager
{
 public:
  void connect ();
  void execute (std::string query);
 public:
  static SqlManager* getInstance ();

 private:
  SqlManager () {};
  
 private:
  pqxx::connection* connection_;
} ;

#endif /* SQLMANAGER_HH_ */
