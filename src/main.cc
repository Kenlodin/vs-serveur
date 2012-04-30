/*
 * main.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include <iostream>

#include "Network/Network.hh"
#include "Tracker/Tracker.hh"
#include "Diffusion/Diffusion.hh"
#include "Thread/Thread.hh"
#include "Thread/ThreadPool.hh"
#include "SqlManager/SqlManager.hh"
#include "Diffusion/HandlingSender.hh"


int main()
{
  //	Network* network = new Network(36000, 36001);
  //	Diffusion* diffusion = new Diffusion();
  //	Tracker* tracker = new Tracker();
  //	return 0;

  //  tools::Thread t();
  //  t.run ();
//  ThreadPool<Diffusion> diffusionWorker (1);
//  ThreadPool<Tracker> trackerWorker(1);
//  HandlingSender handlingSender (1);
  SqlManager::getInstance ().connect ();
//  Network networkManager (36000, 36001);
//  diffusionWorker.start();
//  trackerWorker.start();
//  handlingSender.start();
//  networkManager.run ();
  SqlManager::getInstance ().addServer ("123.456.789", 2546);
  SqlManager::getInstance ().addServer ("123.456.123", 2547);
  //  SqlManager::getInstance ().getThreeServers ();
  //  SqlManager::getInstance ().addServer ("55.22.33.44", 1234);
  //  SqlManager::getInstance ().getThreeServers ();
  //  SqlManager::getInstance ().addClient (5, "88.88.8.88", "127.0.0.1", 150, "azasa5z51dsq1");
  //  SqlManager::getInstance ().addClient ("test", "0fd7bf4aef2dbe4e71ac2cc93e75ed02d9931822", "87.9.152.32", "192.168.0.1", 150);
  return 0;
}

