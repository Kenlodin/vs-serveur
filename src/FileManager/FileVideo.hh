/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILEVIDEO_HH_
#define FILEVIDEO_HH_

# include "../fwd.hh"
# include "Chuck.hh"

class FileVideo
{
  public:
    FileVideo(int videoId);
    FileVideo();
    virtual ~FileVideo();
    virtual Chuck* getPacket(int number) = 0;
    virtual avifile::s_chunk* const* getFileHeader() const = 0;
    int getVideoId() const;
    void setVideoId(int videoId);
  protected:
    int videoId_;
};

#endif /* FILEVIDEO_HH_ */
