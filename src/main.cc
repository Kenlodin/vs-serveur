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

int
main ()
{
  //	Network* network = new Network(36000, 36001);
  //	Diffusion* diffusion = new Diffusion();
  //	Tracker* tracker = new Tracker();
  //	return 0;

  //  tools::Thread t();
  //  t.run ();
    ThreadPool<Diffusion> t (5);
    ThreadPool<Tracker> t2 (5);
//  SqlManager::getInstance ().connect ();
//  SqlManager::getInstance ().getThreeServers ();
//  SqlManager::getInstance ().addServer ("55.22.33.44", 1234);
//  SqlManager::getInstance ().getThreeServers ();

  return 0;
}

