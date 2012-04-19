/*
 * SqlManager.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <stdlib.h>

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
  connection_ = new pqxx::connection("user=aymeric password=test35 host=91.121.55.208 dbname=aymeric");
  connection_->activate ();
  if (connection_->is_open ())
    std::cout << "topmoutout" << std::endl;
  else
  {
    std::cerr << "Impossible de se connecter à la base de données.";
    std::exit (1);
  }
}

void SqlManager::execute (std::string query)
{
  query = query;
  connection_->prepare ("top", "select * from mytable");
  pqxx::work w (*connection_);
  pqxx::result r = w.prepared ("top").exec ();
  std::cout << r.size () << std::endl;
}