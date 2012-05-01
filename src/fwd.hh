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
  typedef unsigned long long u64;
  typedef unsigned int u32;
  typedef unsigned short u16;
  typedef unsigned char u8;
  typedef enum
  {
    OPCODE_RIFF_AVI,
    OPCODE_LIST_HDRL,
    OPCODE_LIST_INFO,
    OPCODE_JUNK,
    OPCODE_LIST_MOVI,
    OPCODE_CHUNK
  } e_opcode;
  typedef struct
  {
      char fcc[4];
      u32 size;
      char name[4];
      void* data;
  } s_chunk;
  typedef struct
      {
          char fcc[4];
          u32 size;
          void *data;
      }__attribute__((packed)) s_sub_chunk;
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

#endif /* FWD_HH_ */
