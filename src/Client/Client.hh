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

class Client
{
  public:
    Client(sf::SocketTCP& control, sf::SocketUDP& data, int videoId);
    virtual ~Client();
    virtual Chuck* getElement(int number) = 0;
    sf::SocketTCP& getControlSocket() const;
    sf::SocketUDP& getDataSocket() const;
    FileVideo* getFileVideo() const;
    void setFileVideo(FileVideo* fileVideo);
    int getVideoId() const;
    void setVideoId(int videoId);

private:
    sf::SocketTCP& controlSocket_;
    sf::SocketUDP& dataSocket_;
    FileVideo* fileVideo_;
    int videoId_;
};

#endif /* CLIENT_H_ */
