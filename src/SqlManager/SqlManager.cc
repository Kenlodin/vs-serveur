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
  //if (connection_->is_open ())
  //{
  pqxx::work w (*connection_);
  pqxx::result r = w.exec (query);
  w.commit ();
  return r;
  //}
}

sql_result
SqlManager::addServer (std::string ip, int port)
{
  std::string req;
  req = "INSERT INTO servers (ip, port) VALUES ('" + ip + "'," + tools::toString (port) + ")";
  return execute (req);
}

std::string
SqlManager::addClient (std::string login, std::string password,
                       std::string public_ip, std::string private_ip,
                       int bandwith)
{
  std::string req;

  // Vérification de l'existance de l'utilisateur
  req = "SELECT id FROM users WHERE username='" + login + "' AND password='" + password + "'";
  sql_result r = execute (req);
  if (r.size () == 0)
    return "";
  
  // Ajout du client 
  std::string user_id = r.at (0)["id"].c_str ();
  std::string token = tools::token (private_ip, public_ip);
  req = "INSERT INTO clients (user_id, public_ip, private_ip, bandwith, token) VALUES ";
  req += "(" + user_id + ", '" + public_ip + "', '" + private_ip + "', ";
  req += tools::toString (bandwith) + ", '" + token + "')";
  execute (req);
  return token;
}

sql_result
SqlManager::saveClientServerConnection (int client_id, int server_id)
{
  std::string req = "INSERT INTO client_server (client_id, server_id, created) VALUES (";
  req += tools::toString (client_id);
  req += ", ";
  req += tools::toString (server_id);
  req += ", 0)";
  return execute (req);
}

sql_result
SqlManager::getThreeServers ()
{
  pqxx::result r = execute ("SELECT * FROM \"servers\" ORDER BY \"nb_client\" LIMIT 3");
  std::cout << r.size () << std::endl;
  for (unsigned long i = 0; i < r.size (); i++)
  {
    pqxx::result::tuple t = r.at (i);
    std::cout << "toto : " << t["ip"] << std::endl;
  }
  //return execute ("SELECT * FROM \"servers\" ORDER BY \"nb_client\" LIMIT 3");
  return r;
}

sql_result
SqlManager::getAllFlux ()
{
  return execute ("SELECT * FROM \"files\"");
}

sql_result
SqlManager::getFile (int id)
{
  //return execute ("SELECT * FROM \"files\" WHERE id=\"" + std::string(id) + "\"");
  return execute ("SELECT * FROM \"files\"");
}