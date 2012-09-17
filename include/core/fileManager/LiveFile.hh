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
# include <core/fileManager/FileVideo.hh>

/**
 * Virtual file that represent a live
 */
class LiveFile : public FileVideo
{
  public:
    /**
     * Constructor
     * @param videoId live id of this file
     */
    LiveFile(int videoId);

    /**
     *  Destructor
     */
    virtual ~LiveFile();

    /**
     *  Get packet
     *  @param number of chunk needed
     *  @return chunk of this live
     */
    Chunk* getElement(int number);

    /**
     *  Insert a new packet
     *  @param number number of chunk received
     *  @param data chunk received
     */
    void setElement(int number, Chunk* data);

    /**
     *  Add linkedServer
     *  @param link server request
     */
    void addServer(sf::SocketTCP);

    /**
     *  Remove linkedServer
     *  @param remove linked server
     */
    void suppServer(sf::SocketTCP);
  private:
    /**
     *  Forward a packet to linked server
     *  @param number number of live chunk received
     *  @param data chunk of live received
     */
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
