/*
 * main.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

# include "Network/Network.hh"
# include "Tracker/Tracker.hh"
# include "Diffusion/Diffusion.hh"

int main(int argc, char **argv) {
	Network* network = new Network(36000, 36001);
	Diffusion* diffusion = new Diffusion();
	Tracker* tracker = new Tracker();
	return 0;
}

