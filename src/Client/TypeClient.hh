/*
 * TypeClient.hh
 *
 *  Created on: 19 avr. 2012
 *      Author: nagriar
 */

#ifndef TYPECLIENT_HH_
#define TYPECLIENT_HH_

# include "../FileManager/Chuck.hh"
# include "../FileManager/FileVideo.hh"
# include "TypeClient.hh"

class TypeClient
{
  public:
    TypeClient(int videoId);
    virtual ~TypeClient();
    virtual Chuck* getElement(int number) = 0;
    int getVideoId() const;
    void setVideoId(int videoId);
    FileVideo* getFileVideo() const;
    void setFileVideo(FileVideo* fileVideo);
  private:
    FileVideo* fileVideo_;
    int videoId_;
};

#endif /* TYPECLIENT_HH_ */
