/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILE_HH_
# define FILE_HH_

//External include
# include <fcntl.h>
# include <unistd.h>
# include <map>
# include <boost/thread/mutex.hpp>

// Internal include
# include "../fwd.hh"
# include "Chuck.hh"
# include "FileVideo.hh"
# include "../Log/Log.hh"
# include "../Tools/Tools.hh"

# define SIZE_CHUNK_HEADER (sizeof(avifile::s_chunk) - sizeof(void*))
# define SIZE_SUBCHUNK_HEADER (sizeof(avifile::s_sub_chunk) - sizeof(void*))
# define MOD2(X) ((X) + (X % 2))
# define MAX(X, Y) (X > Y) ? X : Y

/*
 * Virtual file which represent a vodfile
 */
class VodFile : public FileVideo
{
  public:
    // Constructor
    VodFile();
    VodFile(int videoId);

    // Destructor
    virtual ~VodFile();

    // Get name of file
    std::string getName() const;
  private:
    // Move up to forward packet
    void moveUp(int number);

    // Move down to a previous packet
    void moveDown(int number);

    // Initialise First packet
    void loadSubChunk();

    // Initialise headers
    void loadChunk(avifile::e_opcode type);
  public:
    // Get a chunk
    Chunk* getPacket(int number);

    // Get chunk header
    avifile::s_chunk* const* getFileHeader() const;

    // Return the attribute isValid
    int getIsValid() const;
  private:
    // Check is this VodFile is valid
    int isValid_;

    // file descriptor
    int fd_;

    // Current chunk
    int nbpacket_;

    // Max packet known
    int maxnbpacket_;

    // Video ID
    int videoId_;

    // Current offset
    long offset_;

    // Max offset
    int videoLength_;

    // Link between nbpacket and offset
    std::map<int, long> seekPos_;

    // File headers
    avifile::s_chunk* fileHeader_[5];

    // Name of this file
    std::string name_;

    // Current chunk
    Chunk* currentPacket_;

    // Mutex for move into file
    boost::mutex actionMutex_;
};

// Inline get/set
# include "VodFile.hxx"

#endif /* FILE_HH_ */
