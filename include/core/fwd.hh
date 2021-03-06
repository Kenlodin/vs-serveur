/*
 * fwd.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef FWD_HH_
# define FWD_HH_

# define EXTRACT_TYPE(OPCODE) OPCODE >> 12
# define EXTRACT_CODE(OPCODE) OPCODE % (1 << 12)
# define MERGE_OPCODE(TYPE, CODE) ((TYPE << 12) + CODE)
# define INCTEST(TEST, VAR) if (TEST) {VAR++;}

# define RETURN_VALUE_GOOD 0
# define RETURN_VALUE_ERROR 1
# define RETURN_VALUE_SUPPRESS 2

namespace avifile
{
# define SIZE_CHUNK_HEADER (sizeof(avifile::s_chunk) - sizeof(void*))
# define SIZE_SUBCHUNK_HEADER (sizeof(avifile::s_sub_chunk) - sizeof(void*))
# define MOD2(X) ((X) + (X % 2))

  typedef unsigned long long u64;
  typedef unsigned int u32;
  typedef unsigned short u16;
  typedef unsigned char u8;
  typedef enum
  {
    AVI_RIFF_AVI,
    AVI_LIST_HDRL,
    AVI_LIST_INFO,
    AVI_JUNK,
    AVI_LIST_MOVI,
    AVI_CHUNK
  } e_opcode;
  typedef struct
  {
      char fcc[4];
      u32 size;
      char name[4];
      void* data;
  }__attribute__((packed)) s_chunk;
  
  typedef struct
  {
      char fcc[4];
      u32 size;
      void *data;
  }__attribute__((packed)) s_sub_chunk;
  
  typedef struct
  {
    u32  res4, res5;
    u32  MicroSecPerFrame;
    u32  res0, res1, res2;
    u32  TotalFrame;
  } __attribute__((packed)) s_hdrl;
  
}

namespace ConnexionType
{
  enum ConnexionType
  {
    CLIENT_TRACKER,
    TRACKER_CLIENT,
    CLIENT_DIFFUSION,
    DIFFUSION_CLIENT,
    DIFFUSION_DIFFUSION,
    ALL,
    ADMIN_SERVER,
    LENGTH
  };
}
namespace CT
{
  enum CT
  {
    CONN_MASTER,
    CONN_SLAVE,
    ASK_LIST,
    ASK_FLUX,
    ASK_CHECK,
    ASK_PACKET,
    ASK_RPACKET,
    ASK_MOVE,
    ASK_DEFICIENT,
    ASK_REM,
    ASK_STOP,
    DEC,
    PING,
    URL,
    LENGTH
  };
}

namespace TC
{
  enum TC
  {
    TOKEN,
    LIST,
    LIST_DIFF,
    LIST_NDIFF,
    MSG,
    PING,
    URL,
    LENGTH
  };
}

namespace CD
{
  enum CD
  {
    CD_TOKEN,
    LENGTH
  };
}

namespace DC
{
  enum DC
  {
    DATA,
    MSG,
    LENGTH
  };
}

namespace DD
{
  enum DD
  {
    VIDEO_DEMAND,
    PING_PONG,
    LIVE_LINK,
    LIVE_DATA,
    VOD_DATA,
    LENGTH
  };
}

namespace AS
{
    enum AS
    {
        SHUTDOWN,
        CLEAR,
        DOWNLOAD_ORIG,
        DOWNLOAD,
        REMOVE,
        MAX_VALUE
    };
}

#endif /* FWD_HH_ */
