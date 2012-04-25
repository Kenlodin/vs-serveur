/*
 * File.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef FILE_HH_
#define FILE_HH_

# include <fstream>
# include "../fwd.hh"
# include "Chuck.hh"
# include "FileVideo.hh"
# include "../Log/Log.hh"
# include <fcntl.h>
# include <unistd.h>
# include <map>

# define SIZE_CHUNK_HEADER (sizeof(avifile::s_chunk) - sizeof(void*))
# define SIZE_SUBCHUNK_HEADER (sizeof(avifile::s_sub_chunk) - sizeof(void*))
# define MOD2(X) ((X) + (X % 2))
# define MAX(X, Y) (X > Y) ? X : Y

class VodFile : public FileVideo
{
  public:
    VodFile();
    VodFile(int videoId);
    virtual ~VodFile();
    std::string getName() const;
  private:
    void moveUp(int number);
    void moveDown(int number);

    void loadSubChunk();
    void loadChunk(avifile::e_opcode type);
  public:
    Chuck* getPacket(int number);
    avifile::s_chunk* const* getFileHeader() const;
  private:
    int fd_;
    int nbpacket_;
    int maxnbpacket_;
    int videoId_;
    long offset_;
    int videoLength_;
    std::map<int, long> seekPos_;
    avifile::s_chunk* fileHeader_[5];
    std::string name_;
    Chuck* currentPacket_;
};

#endif /* FILE_HH_ */
