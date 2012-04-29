/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILEVIDEO_HH_
# define FILEVIDEO_HH_

// Internal include
# include "../fwd.hh"
# include "Chuck.hh"

/*
 * Abstract class which represent a virtual file
 */
class FileVideo
{
  public:
    // Constructors
    FileVideo(int videoId);
    FileVideo();

    // Destructor
    virtual ~FileVideo();

    //  Get a chunck
    virtual Chunk* getPacket(int number) = 0;

    // Get header of avi
    virtual avifile::s_chunk* const* getFileHeader() const = 0;

    // Get video ID
    int getVideoId() const;

    // Set video ID
    void setVideoId(int videoId);
  protected:
    // Video ID
    int videoId_;
};

// Inline Get/Set
# include "FileVideo.hxx"

#endif /* FILEVIDEO_HH_ */
