/*
 * SqlManager.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "SqlManager.hh"

SqlManager&
SqlManager::getInstance ()
{
  static SqlManager instance;

  return instance;
}

void
SqlManager::connect ()
{
  connection_ = new pqxx::connection ("user=aymeric password=test35 host=91.121.55.208 dbname=aymeric");
  connection_->activate ();
  if (!connection_->is_open ())
  {
    std::cerr << "Impossible de se connecter à la base de données.";
  }
}

pqxx::result
SqlManager::execute (std::string query)
{
  query = query;
  std::cout << connection_ << std::endl;
  //if (connection_->is_open ())
  //{
    connection_->prepare ("top", query);
    pqxx::work w (*connection_);
    pqxx::result r = w.prepared ("top").exec ();
    return r;
  //}
}

sql_result
SqlManager::getThreeServers ()
{
  pqxx::result r = execute ("SELECT * FROM \"servers\" ORDER BY \"nb_client\" LIMIT 3");
  sql_result result;
  for (unsigned long i = 0; i < r.size (); i++)
  {
    pqxx::result::tuple t = r.at (i);
    map m;
    m.insert (pair ("ip", std::string(t["ip"].c_str ())));
    m.insert (pair ("port", std::string(t["port"].c_str ())));
    result.push_back (m);
  }
  return result;
}
