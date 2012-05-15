/* 
 * File:   Http.hh
 * Author: aymeric
 *
 * Created on 14 mai 2012, 21:29
 */

#ifndef HTTP_HH
#define	HTTP_HH
#include <curl/curl.h>
#include "../../Log/Log.hh"
namespace tools
{

  class Http
  {
  public:
    static size_t writeFile (void *ptr, size_t size, size_t nmemb, FILE *stream);
    static int download(std::string url, std::string file);
  
  private:
    Http();
    virtual ~Http();
  };
}
#endif	/* HTTP_HH */

