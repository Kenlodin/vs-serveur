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

 public:
  static SqlManager* getInstance ();

 private:
  SqlManager () {};
  
 private:
  pqxx::connection* connection;
} ;

#endif /* SQLMANAGER_HH_ */
