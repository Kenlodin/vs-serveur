/* 
 * File:   ChunckCounter.hh
 * Author: aymeric
 *
 * Created on 16 mai 2012, 00:34
 */

#ifndef CHUNCKCOUNTER_HH
#define	CHUNCKCOUNTER_HH

#include <core/fwd.hh>
#include <core/log/Log.hh>
namespace tools
{

  class ChunckCounter
  {
  public:

    struct result
    {
      int size;
      int length;
      int nb_packet;
    };

  private:
    ChunckCounter();
    virtual ~ChunckCounter();

  public:
    /**
     * Return some informations about a avi file
     * @param file
     * @return 
     */
    static struct result avi(std::string file);
  };
}
#endif	/* CHUNCKCOUNTER_HH */

