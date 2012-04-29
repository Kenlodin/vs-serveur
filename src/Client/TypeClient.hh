/*
 * TypeClient.hh
 *
 *  Created on: 19 avr. 2012
 *      Author: nagriar
 */

#ifndef TYPECLIENT_HH_
# define TYPECLIENT_HH_

// Internal include
# include "../FileManager/Chuck.hh"
# include "../FileManager/FileVideo.hh"
# include "TypeClient.hh"

/*
 * Abstract client which provide the same method to get chuck
 * regardless type of video
 */
class TypeClient
{
  public:
    // Constructor
    TypeClient(int videoId);

    // Destructor
    virtual ~TypeClient();

    // Virtual method to get a chuck
    virtual Chunk* getElement(int number) = 0;

    // Get video ID
    int getVideoId() const;

    // Get file video
    FileVideo* getFileVideo() const;

    // Set file video
    void setFileVideo(FileVideo* fileVideo);
  private:
    // Save virtual file which represent video
    FileVideo* fileVideo_;

    // Video id
    int videoId_;
};

// Inline get/set
# include "TypeClient.hxx"

#endif /* TYPECLIENT_HH_ */
