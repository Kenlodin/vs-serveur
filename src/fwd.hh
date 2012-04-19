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


# define RETURN_VALUE_GOOD 0
# define RETURN_VALUE_ERROR 1
# define RETURN_VALUE_SUPPRESS 2

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
		LENGTH
	};
}

#endif /* FWD_HH_ */
