/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILE_HH_
#define FILE_HH_

# include <fstream>
# include "FileVideo.hh"

class VodFile : public FileVideo
{
  public:
    VodFile();
    VodFile(int videoId);
    virtual ~VodFile();
    int getFd() const;
    void setFd(int fd);
    std::string getName() const;
    void setName(std::string name);
    int getNbpacket() const;
    void setNbpacket(int nbpacket);
  public:
    Chuck* getPacket(int number);

  private:
    void moveUp(int number);
    void moveDown(int number);

  private:
    int fd_;
    int nbpacket_;
    int videoId_;
    std::string name_;
    Chuck* currentPacket_;
    std::fstream file_;
};

#endif /* FILE_HH_ */
