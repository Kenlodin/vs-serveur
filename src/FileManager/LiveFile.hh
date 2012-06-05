/*
 * LiveFile.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVEFILE_HH_
# define LIVEFILE_HH_

// External include
# include <boost/thread/mutex.hpp>
# include <map>
# include <list>
# include <SFML/Network.hpp>

// Internal include
# include "FileVideo.hh"

/*
 * Virtual file that represent a live
 */
class LiveFile : public FileVideo
{
  public:
    LiveFile(int videoId);

    // Destructor
    virtual ~LiveFile();

    // Get packet
    Chunk* getElement(int number);

    // Insert a new packet
    void setElement(int number, Chunk* data);

    // Add linkedServer
    void addServer(sf::SocketTCP);

    // Remove linkedServer
    void suppServer(sf::SocketTCP);
  private:
    // Forward a packet to linked server
    void forwardPacket(int number, Chunk* data);
  private:
    // Contain every live packet.
    std::map<int, Chunk*> packets_;

    // Mutex for packets_
    boost::mutex packetsMutex_;

    // List of linked server
    std::list<sf::SocketTCP> linkedServer_;

    // Mutex for linkedServer_
    boost::mutex linkedServerMutex_;
};

#endif /* LIVEFILE_HH_ */
