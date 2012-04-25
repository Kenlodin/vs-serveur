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
# include <fcntl.h>
# include <unistd.h>
# include <map>

# define SIZE_CHUNK_HEADER (sizeof(s_chunk) - sizeof(void*))
# define SIZE_SUBCHUNK_HEADER (sizeof(Chuck::s_sub_chunk) - sizeof(void*))
# define MOD2(X) ((X) + (X % 2))
# define MAX(X, Y) (X > Y) ? X : Y

class VodFile : public FileVideo
{
  private:
    typedef unsigned long long u64;
    typedef unsigned int u32;
    typedef unsigned short u16;
    typedef unsigned char u8;
  public:
    VodFile();
    VodFile(int videoId);
    virtual ~VodFile();
    std::string getName() const;
  private:
    void moveUp(int number);
    void moveDown(int number);
    typedef struct
    {
        char fcc[4];
        u32 size;
        char name[4];
        void* data;
    } s_chunk;
    void loadSubChunk();
    void loadChunk(e_opcode type);
  public:
    Chuck* getPacket(int number);
    s_chunk* const* getFileHeader() const;
  private:
    int fd_;
    int nbpacket_;
    int maxnbpacket_;
    int videoId_;
    long offset_;
    int videoLength_;
    std::map<int, long> seekPos_;
    s_chunk* fileHeader_[5];
    std::string name_;
    Chuck* currentPacket_;
};

#endif /* FILE_HH_ */
