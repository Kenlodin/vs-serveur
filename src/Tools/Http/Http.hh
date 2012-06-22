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
    /**
     * Write a file on disk
     * @param ptr
     * @param size
     * @param nmemb
     * @param stream
     * @return 
     */
    static size_t writeFile (void *ptr, size_t size, size_t nmemb, FILE *stream);
    
    /**
     * Download a file from an HTTP server
     * @param url
     * @param file
     * @return 
     */
    static int download(std::string url, std::string file);
  
  private:
    Http();
    virtual ~Http();
  };
}
#endif	/* HTTP_HH */

