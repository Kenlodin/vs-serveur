/*
 * SqlManager.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <sys/param.h>
#include <boost/thread/pthread/mutex.hpp>

#include <core/sqlManager/SqlManager.hh>
#include <core/tools/Tools.hh>

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
  //if (connection_->is_open ())
  //{
  //COUTDEBUG("\t SQL Query exexute : " + query);
  mutex_.lock ();
  pqxx::work w (*connection_);
  pqxx::result r = w.exec (query);
  w.commit ();
  mutex_.unlock ();
  //  COUTDEBUG("\t  => Nb result : " + tools::toString <int> (r.size ()));
  return r;
  //}
}

void
SqlManager::addServer (std::string ip, int port)
{
  std::string req;
  int id;
  execute ("DELETE FROM servers WHERE ip='" + ip + "'");
  req = "INSERT INTO servers (ip, port) VALUES ('" + ip + "'," + tools::toString<int> (port) + ") RETURNING id";
  sql_result r = execute (req);
  r.at (0)["id"].to<int>(id);
  Config::getInstance ().add ("server_id", id);
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
  std::string req = "INSERT INTO client_server (client_token, server_id, created) VALUES ('";
  req += client_token;
  req += "', ";
  req += tools::toString<int> (server_id);
  req += ", 0)";
  return execute (req);
}

void
SqlManager::removeClientServerConnection (std::string client_token, int server_id)
{
  execute ("DELETE FROM client_server WHERE client_token='" + client_token + "' AND server_id="+tools::toString<int> (server_id));
}

void
SqlManager::setHandlings (std::string client_token, int file_id)
{
  int nb_packet;
  int length;
  std::string str_nb_packet;
  sql_result r = execute ("SELECT * FROM \"files\" WHERE id='" + tools::toString<int> (file_id) + "'");
  if (r.size () > 0)
  {
    tools::fromString (r.at (0)["nb_packet"].c_str (), nb_packet);
    tools::fromString (r.at (0)["length"].c_str (), length);
    str_nb_packet = std::string (r.at (0)["nb_packet"].c_str ());

    int coeff = ((float) nb_packet / (float) length) * 10;
    int date = static_cast<int> (time (0));

    execute ("select set_handlings (" + str_nb_packet + ", "
             + tools::toString<int> (date) + ", "
             + tools::toString<int> (coeff) + ", "
             + tools::toString<int> (file_id) + ", '"
             + client_token + "')");
  }
}

sql_result
SqlManager::getThreeServers ()
{
  return execute ("SELECT * FROM \"servers\" ORDER BY \"nb_client\" LIMIT 3");
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
    return execute ("\
            UPDATE client_handlings\
            SET status=1\
            FROM\
                (SELECT client_handlings.id,\
                        client_handlings.client_token,\
                        client_handlings.packet_begin,\
                        client_handlings.packet_end,\
                        client_handlings.file_id\
                FROM client_server\
                LEFT JOIN client_handlings\
                ON client_server.client_token = client_handlings.client_token\
                WHERE client_server.server_id='" + tools::toString<int> (server_id) + "' \
                AND status=0\
                ORDER BY client_handlings.date\
                LIMIT 1)\
            AS s \
            WHERE client_handlings.id = s.id \
            RETURNING s.client_token,\
                    s.packet_begin,\
                    s.packet_end,\
                    s.file_id ;\
        ");
}

sql_result
SqlManager::getServerForDD (int video_id)
{
  return execute ("\
          SELECT * FROM servers, file_server \
          WHERE servers.id = file_server.server_id \
           AND file_server.file_id = " + tools::toString<int> (video_id) + " \
          ORDER BY nb_client \
          LIMIT 1 \
          ");
}

sql_result
SqlManager::setFileServer (int file_id)
{
  return setFileServer (tools::toString<int> (file_id));
}

sql_result
SqlManager::setFileServer (std::string file_id)
{
  std::string req;
  int server_id = Config::getInstance ().getInt ("server_id");
  req = "INSERT INTO file_server (server_id, file_id) VALUES(" + tools::toString<int> (server_id) + ", " + file_id + ")";
  return execute (req);
}

void SqlManager::updateFileInfos (int id, int size, int length, int nb_packet)
{
  execute(""
          " UPDATE files"
          " SET size=" + tools::toString<int> (size) + ","
          "    length=" + tools::toString<int> (length) + ","
          "    nb_packet=" + tools::toString<int> (nb_packet) + 
          " WHERE id=" + tools::toString<int> (id) +
          "");
}

void
SqlManager::disconnectServer (int server_id)
{
  execute ("DELETE FROM servers WHERE id='" + tools::toString<int> (server_id) + "'");
}

void
SqlManager::disconnectClient (std::string token)
{
  execute ("DELETE FROM clients WHERE token='" + token + "'");
  execute ("DELETE FROM client_server WHERE client_token='" + token + "'");
  execute ("DELETE FROM client_handlings WHERE client_token='" + token + "'");
}

void SqlManager::deleteHandlings (std::string token)
{
  execute ("DELETE FROM client_handlings WHERE client_token='" + token + "'");
}
