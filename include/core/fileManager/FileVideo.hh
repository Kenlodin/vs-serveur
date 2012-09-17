/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILEVIDEO_HH_
# define FILEVIDEO_HH_

// Internal include
# include <core/fwd.hh>
# include <core/fileManager/Chuck.hh>

/**
 * Abstract class which represent a virtual file
 */
class FileVideo
{
  public:
    /**
     *  Constructors
     *  @param videoId id of this video file
     */
    FileVideo(int videoId);
    /**
     * Constructor
     */
    FileVideo();

    /**
     *  Destructor
     */
    virtual ~FileVideo();

    /**
     *   Get a chunck
     *   @param number number of chunk needed
     *   @return Chunk need to be delete
     */
    virtual Chunk* getElement(int number) = 0;

    /*
     *   Set a chunk
     *   @param number number of chunk received
     *   @param packet chunk received
     */
    virtual void setElement(int number, Chunk* packet) = 0;

    /**
     *  Get header of avi
     *  @return array of avi header
     */
    virtual avifile::s_chunk* const* getFileHeader() const = 0;

    /**
     *  Get video ID
     *  @return id of this video
     */
    int getVideoId() const;

    /**
     *  Set video ID
     *  @param videoId set videoId of this file
     */
    void setVideoId(int videoId);
  protected:
    // Video ID
    int videoId_;
};

// Inline Get/Set
# include <core/fileManager/FileVideo.hxx>

#endif /* FILEVIDEO_HH_ */
