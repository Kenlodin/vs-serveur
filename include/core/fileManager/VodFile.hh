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
# include <core/fwd.hh>
# include <core/fileManager/Chuck.hh>
# include <core/fileManager/FileVideo.hh>
# include <core/log/Log.hh>
# include <core/tools/Tools.hh>

# define MAX(X, Y) (X > Y) ? X : Y

/*
 * Virtual file which represent a vodfile
 */
class VodFile : public FileVideo
{
  public:
    /**
     *  Constructor
     */
    VodFile();
    /**
     * Constructor
     * @param videoId id of this video
     */
    VodFile(int videoId);

    /**
     *  Destructor
     */
    virtual ~VodFile();

    /**
     *  Get name of file
     *  @return the name of this file
     */
    std::string getName() const;
  private:
    /**
     *  Move up to forward packet
     *  @param number of chunk needed
     */
    void moveUp(int number);

    /**
     *  Move down to a previous packet
     *  @param number of chunk needed
     */
    void moveDown(int number);

    /**
     *  Initialise First packet
     */
    void loadSubChunk();

    /**
     *  Initialise headers
     *  @param type type identifier of this header
     */
    void loadChunk(avifile::e_opcode type);
  public:
    /**
     *  Get a chunk
     *  @param number of chunk needed
     *  @return chunk readed
     */
    Chunk* getElement(int number);


    /**
     *  Get a chunk
     *  @param number of chunk to write
     *  @param element chunk to write
     */
    void setElement(int number, Chunk* element);

    /**
     *  Get chunk header
     *  @return array of header
     */
    avifile::s_chunk* const* getFileHeader() const;

    /**
     *  Return the attribute isValid
     *  @return RETURN_VALUE_GOOD if this file is valid
     */
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
# include <core/fileManager/VodFile.hxx>

#endif /* FILE_HH_ */
