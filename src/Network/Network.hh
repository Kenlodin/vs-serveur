/*
 * Network.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef NETWORK_HH_
#define NETWORK_HH_

# include <SFML/System.hpp>
# include <SFML/Network.hpp>
# include <pthread.h>

class Network {
public:
	Network(int control_port, int data_port);
	virtual ~Network();
	int start();
private:
	sf::SocketTCP* control_socket_;
	sf::SocketTCP* data_socket_;
	unsigned short control_port_;
	unsigned short data_port_;
	pthread_t* control_thread;
	pthread_t* data_thread;
};

#endif /* NETWORK_HH_ */
