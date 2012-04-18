/*
 * SqlManager.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "SqlManager.hh"

SqlManager* SqlManager::getInstance ()
{
  static SqlManager* instance = nullptr;
  if (instance == nullptr)
    instance = new SqlManager ();
  return instance;
}

void SqlManager::connect ()
{
  connection = new pqxx::connection("");
  connection->activate ();
  if (connection->is_open ())
    std::cout << "topmoutout" << std::endl;
  else
    std::cout << "NOOOOO" << std::endl;
}