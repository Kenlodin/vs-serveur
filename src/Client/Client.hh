/*
 * Client.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_H_
#define CLIENT_H_

# include "../FileManager/Chuck.hh"
# include "../FileManager/FileVideo.hh"
# include <SFML/Network.hpp>
# include "../fwd.hh"

class Client
{
  public:
    Client(sf::SocketTCP& control, sf::SocketTCP& data, int videoId);
    virtual ~Client();
    virtual Chuck* getElement(int number) = 0;
    sf::SocketTCP& getControlSocket() const;
    sf::SocketTCP& getDataSocket() const;
    FileVideo* getFileVideo() const;
    void setFileVideo(FileVideo* fileVideo);
    int getVideoId() const;
    void setVideoId(int videoId);
    int sendControl(sf::Packet& packet);
    int sendData(sf::Packet& packet);
private:
    sf::SocketTCP& controlSocket_;
    sf::SocketTCP& dataSocket_;
    FileVideo* fileVideo_;
    int videoId_;
};

#endif /* CLIENT_H_ */
