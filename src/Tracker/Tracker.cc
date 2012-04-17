/*
 * Tracker.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Tracker.hh"

Tracker::Tracker()
	: route_ ({
		&Tracker::ctConnMaster,
		&Tracker::ctConnSlave,
		&Tracker::ctAskList,
		&Tracker::ctAskFlux,
		&Tracker::ctAskCheck,
		&Tracker::ctAskPacket,
		&Tracker::ctAskRpacket,
		&Tracker::ctAskMove,
		&Tracker::ctAskDeficient,
		&Tracker::ctAskRem,
		&Tracker::ctAskStop,
		&Tracker::ctDec,
})
{
	// TODO Auto-generated constructor stub


}

Tracker::~Tracker() {
	// TODO Auto-generated destructor stub
}

int Tracker::routing(unsigned int code, sf::Packet* packet) {
	if (code < CT::LENGTH)
		(this->*route_[code]) (packet);
	else
		return TRUE;
	return FALSE;
}

int Tracker::ctConnMaster(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctConnSlave(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskList(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskFlux(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskCheck(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskPacket(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskRpacket(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskMove(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskDeficient(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctAskRem(sf::Packet* packet) {
	return FALSE;
}


int Tracker::ctAskStop(sf::Packet* packet) {
	return FALSE;
}

int Tracker::ctDec(sf::Packet* packet) {
	return FALSE;
}
