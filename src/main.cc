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

int
main ()
{
  //	Network* network = new Network(36000, 36001);
  //	Diffusion* diffusion = new Diffusion();
  //	Tracker* tracker = new Tracker();
  //	return 0;
  sf::Clock Clock;
  while (Clock.GetElapsedTime () < 5.f)
  {
    std::cout << Clock.GetElapsedTime () << std::endl;
    sf::Sleep (0.5f);
  }

  return 0;
}

