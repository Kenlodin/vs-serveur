/*
 * SqlManager.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <sys/param.h>

#include "SqlManager.hh"
#include "../Tools/Tools.hh"

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
  req = "INSERT INTO servers (ip, port) VALUES ('" + ip + "'," + tools::toString<int> (port) + ")";
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
  req += tools::toString<int> (bandwith) + ", '" + token + "')";
  execute (req);
  return token;
}

sql_result
SqlManager::saveClientServerConnection (std::string client_token, int server_id)
{
  std::string req = "INSERT INTO client_server (client_id, server_id, created) VALUES (";
  req += client_token;
  req += ", ";
  req += tools::toString<int> (server_id);
  req += ", 0)";
  return execute (req);
}

/**
 * @todo : return a boolean
 * @param client_token
 * @param file_id
 * @return 
 */
sql_result
SqlManager::setHandlings (std::string client_token, int file_id)
{
  sql_result r = execute ("SELECT * FROM \"files\" WHERE id='" + tools::toString<int> (file_id) + "'");
  if (r.size () > 0)
  {
    int nb_packet;
    int length;
    tools::fromString (r.at (0)["nb_packet"].c_str (), nb_packet);
    tools::fromString (r.at (0)["length"].c_str (), length);
    float coeff = (nb_packet / length) * 10;
    int date = static_cast<int> (time (0));
    std::cout << "nb packet : " << nb_packet << std::endl;
    for (int i = 0; i < nb_packet; i += 10)
    {
      std::cout << "i : " << i << std::endl;
      std::string req = "INSERT INTO client_handlings (client_token, file_id, date, packet_begin, packet_end) VALUES ('" +
        client_token + "', " + tools::toString<int> (file_id) + ", " + tools::toString<int> (date) +
        ", " + tools::toString<int> (i) + ", " + tools::toString<int> (i + 10) + ")";
      std::cout << req << std::endl;
      date += coeff;
      execute (req);
    }
  }
  return r;
}

sql_result
SqlManager::getThreeServers ()
{
  return execute ("SELECT * FROM \"servers\" ORDER BY \"nb_client\" LIMIT 3");
  //  std::cout << r.size () << std::endl;
  //  for (unsigned long i = 0; i < r.size (); i++)
  //  {
  //    pqxx::result::tuple t = r.at (i);
  //    std::cout << "toto : " << t["ip"] << std::endl;
  //  }
}

sql_result
SqlManager::getAllFlux ()
{
  return execute ("SELECT * FROM \"files\"");
}

sql_result
SqlManager::getFlux (int id)
{
  return execute ("SELECT * FROM \"files\" WHERE id='" + tools::toString<int> (id) + "'");
}

sql_result
SqlManager::getNextsHandlings (int server_id)
{
  std::string req;
  req = "SELECT client_handlings.client_token, client_handlings.packet_id FROM client_server LEFT JOIN client_handlings ON ";
  req += "(client_server.client_token = client_handlings.client_token)";
  req += "WHERE client_server.server_id='" + tools::toString<int> (server_id) + "'";
  return execute (req);
}
