/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILEVIDEO_HH_
#define FILEVIDEO_HH_

typedef enum
{
  OPCODE_RIFF_AVI,
  OPCODE_LIST_HDRL,
  OPCODE_LIST_INFO,
  OPCODE_JUNK,
  OPCODE_LIST_MOVI,
  OPCODE_CHUNK
} e_opcode;

# include "Chuck.hh"

class FileVideo
{
  public:
    FileVideo(int videoId);
    FileVideo();
    virtual ~FileVideo();
    virtual Chuck* getPacket(int number) = 0;
    int getVideoId() const;
    void setVideoId(int videoId);
  protected:
    int videoId_;
};

#endif /* FILEVIDEO_HH_ */
