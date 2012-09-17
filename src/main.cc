/*
 * main.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include <iostream>

# include <SFML/System.hpp>
# include <SFML/Network.hpp>
# include <signal.h>

#include <core/network/Network.hh>
#include <core/tracker/Tracker.hh>
#include <core/diffusion/Diffusion.hh>
#include <core/thread/Thread.hh>
#include <core/thread/ThreadPool.hh>
#include <core/sqlManager/SqlManager.hh>
#include <core/diffusion/HandlingSender.hh>
#include <core/adminServer/AdminServer.hh>


void sig_pipe(int num __attribute__((unused)))
{
  signal(SIGPIPE, sig_pipe);
  return;
}

int
main ()
{
  //	Network* network = new Network(36000, 36001);
  //	Diffusion* diffusion = new Diffusion();
  //	Tracker* tracker = new Tracker();
  //	return 0;

  //  tools::Thread t();
  //  t.run ();
  signal(SIGPIPE, sig_pipe);
  SqlManager::getInstance ().connect ();
  Config::getInstance ().load ("config.xml");
  Config::getInstance ().loadConfig ();
  sf::IPAddress address (Config::getInstance ().getString ("ip"));
  if (!address.IsValid())
  {
    std::cerr << "L'adresse ip indiquée dans config.xml n'est pas bonne" << std::endl;
    exit(2);
  }
  SqlManager::getInstance ().addServer (Config::getInstance ().getString ("ip"),
                                        36001); //TODO port
  Config::getInstance ().loadFiles ();
  ThreadPool<Diffusion> diffusionWorker (1);
  ThreadPool<Tracker> trackerWorker (1);
  ThreadPool<AdminServer> adminWorker (1);
  HandlingSender handlingSender (1);
  Network networkManager (36000, 36001); // TODO Port
  diffusionWorker.start ();
  trackerWorker.start ();
  adminWorker.start ();
  handlingSender.start ();
  networkManager.run ();

  COUTDEBUG("Attente de la fin des threads.");
  diffusionWorker.join ();
  trackerWorker.join ();
  adminWorker.join ();
  handlingSender.join ();
  COUTDEBUG("Tous les threads sont terminés, le serveur va s'éteindre ...");

  //  SqlManager::getInstance ().getThreeServers ();
  //  SqlManager::getInstance ().addServer ("55.22.33.44", 1234);
  //  SqlManager::getInstance ().getThreeServers ();
  //  SqlManager::getInstance ().addClient (5, "88.88.8.88", "127.0.0.1", 150, "azasa5z51dsq1");
  //  SqlManager::getInstance ().addClient ("test", "0fd7bf4aef2dbe4e71ac2cc93e75ed02d9931822", "87.9.152.32", "192.168.0.1", 150);
  return 0;
}

